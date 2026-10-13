#!/usr/bin/env python3
"""Compile source candidates, link at ROM addresses, and compare entire extents."""

import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
from datetime import datetime, timezone
import uuid
import struct

from elftools.elf.elffile import ELFFile
from project import ROOT, audit, compare_bytes, write_report
from toolchain import (load_profile, verify_native, ARM_PIN, ARM_PROFILE,
                       GCC302_PIN, GCC302_PROFILE, GCC302_HWI32_PIN,
                       GCC302_HWI32_PROFILE, compiler_selection,
                       verify_gcc302_source, optimization_flags, assembler_selection,
                       BINUTILS2101_PIN, BINUTILS2101_PROFILE, verify_binutils2101_source,
                       modern_assembler_abi_flags)
from source_symbols import declarations
from source_controls import mutate, require_negative_controls, verified_comparison
from source_addresses import execution_address, validate_execution_layout, validate_symbol_definitions
from ram_copies import validate_copy
from header_snapshots import (snapshot_headers, retained_source, verify_snapshot_inputs,
                              verify_preprocessor_dependencies)
from source_coverage import byte_counts, inline_glue, verify_inline_glue_symbols


def run(command, commands):
    commands.append([str(arg) for arg in command])
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode:
        raise RuntimeError(f"Command failed: {commands[-1]}\n{result.stderr[-6000:]}")
    return result.stdout


def compile_function(function, source, folder, flags, copies=None, header_overrides=None):
    folder.mkdir(parents=True, exist_ok=True)
    commands = []
    header_folder = folder / "include"
    headers = snapshot_headers(source, header_folder, ROOT / 'include')
    for name, text in (header_overrides or {}).items():
        if name not in headers['headers']:
            raise ValueError('Header control is outside the source include closure')
        (header_folder / name).write_text(text)
        headers['headers'][name] = hashlib.sha256(text.encode()).hexdigest()
    (folder / 'header-snapshot.json').write_text(json.dumps(headers, indent=2) + '\n')
    preprocessed = folder / "source.i"
    assembly = folder / "source.s"
    obj = folder / "source.o"
    linked = folder / "linked.elf"
    entries = ()
    if copies is None:
        ram = json.loads((ROOT / 'config/ram-map-us-eu.json').read_text())
        copies, entries = ram['copies'], ram['entries']
    address = execution_address(function, copies, entries)
    selected = compiler_selection(function, flags)
    selected_assembler = assembler_selection(function)
    compiler = ROOT / selected['executable']
    flags = selected['flags']
    retained = retained_source(headers, header_folder)
    dependencies = folder / 'preprocessor.d'
    run(["xcrun", "clang", "--target=arm-none-eabi", "-E", "-P", "-undef",
         "-nostdinc", "-std=gnu89", "-MD", "-MF", dependencies, "-MT", "snapshot",
         "-I", header_folder, retained, "-o", preprocessed], commands)
    verify_snapshot_inputs(headers, header_folder)
    headers['preprocessor_dependencies'] = verify_preprocessor_dependencies(
        headers, header_folder, dependencies)
    dependency_digest = hashlib.sha256(dependencies.read_bytes()).hexdigest()
    headers['preprocessor_dependency_sha256'] = dependency_digest
    (folder / 'header-snapshot.json').write_text(json.dumps(headers, indent=2) + '\n')
    run([compiler, *flags, preprocessed, "-o", assembly], commands)
    verify_snapshot_inputs(headers, header_folder)
    assembler = ROOT / selected_assembler['executable']
    run([assembler, *selected_assembler['source_flags'], assembly, "-o", obj], commands)
    # Mark external function addresses as Thumb, so the linker does not invent
    # ARM interworking veneers for absolute ROM symbols.
    externs = folder / "externs.s"
    externs.write_text("\n".join(declarations(function.get('symbols', {}),
                                            function.get('thumb_symbols', ()))) + "\n")
    extern_obj = folder / "externs.o"
    run([assembler, *selected_assembler['extern_flags'], externs, "-o", extern_obj], commands)
    script = folder / "function.ld"
    script.write_text(f"SECTIONS {{ .text {address:#x} : {{ *(.text) . = ALIGN(4); }} = 0 }}\n")
    run([ROOT / "toolchains/binutils/bin/arm-none-eabi-ld", "-T", script,
         f"--entry={function['name']}", obj, extern_obj, "-o", linked], commands)
    with linked.open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(".text")
        if section["sh_addr"] != address:
            raise RuntimeError("Linked text is at the wrong address")
        if any(s["sh_type"] in ("SHT_REL", "SHT_RELA") and s["sh_size"]
               for s in elf.iter_sections()):
            raise RuntimeError("Linked output retains unresolved relocations")
        data = section.data()
        symtab = elf.get_section_by_name(".symtab")
        symbol = symtab.get_symbol_by_name(function["name"])[0]
        functions = [s for s in symtab.iter_symbols() if s["st_info"]["type"] == "STT_FUNC"
                     and s["st_shndx"] == elf.get_section_index(".text")]
        # GNU as can append section-alignment padding after the .size extent.
        # Include it in the comparison; never strip it to manufacture a match.
        tail_size = len(data) - symbol["st_size"]
        if ((symbol["st_value"] & ~1) != address or len(functions) != 1
                or not 0 <= tail_size < section["sh_addralign"]):
            raise RuntimeError("Function does not own the complete linked text extent")
        verify_inline_glue_symbols(function,
                                   {s.name: s['st_value'] for s in symtab.iter_symbols()
                                    if s['st_shndx'] == elf.get_section_index('.text')}, address)
    verify_snapshot_inputs(headers, header_folder)
    if hashlib.sha256(dependencies.read_bytes()).hexdigest() != dependency_digest:
        raise ValueError('Preprocessor dependency receipt changed during compilation')
    return data, commands


def assemble_glue(region, source, folder):
    """Assemble explicit low-level glue. It is never matching C coverage."""
    folder.mkdir(parents=True, exist_ok=True)
    commands = []
    assembler = ROOT / 'toolchains/binutils/bin/arm-none-eabi-as'
    obj, linked = folder / 'source.o', folder / 'linked.elf'
    run([assembler, '-mcpu=arm7tdmi', '--no-pad-sections', *modern_assembler_abi_flags(),
         source, '-o', obj], commands)
    externs = folder / 'externs.s'
    externs.write_text('\n'.join(declarations(region.get('symbols', {})))+'\n')
    extern_obj = folder / 'externs.o'
    run([assembler, *modern_assembler_abi_flags(), externs, '-o', extern_obj], commands)
    address = 0x08000000 + region['rom_offset']
    script = folder / 'function.ld'
    script.write_text(f'SECTIONS {{ .text {address:#x} : {{ *(.text) }} }}\n')
    run([ROOT / 'toolchains/binutils/bin/arm-none-eabi-ld', '-T', script,
         obj, extern_obj, '-o', linked], commands)
    with linked.open('rb') as stream:
        elf = ELFFile(stream)
        allocated = [s for s in elf.iter_sections() if s['sh_flags'] & 2 and s['sh_size']]
        if len(allocated) != 1 or allocated[0].name != '.text' or allocated[0]['sh_addr'] != address:
            raise ValueError('Glue has unexpected allocated sections or address')
        if any(s['sh_type'] in ('SHT_REL', 'SHT_RELA') and s['sh_size'] for s in elf.iter_sections()):
            raise ValueError('Glue retains unresolved relocations')
        data = allocated[0].data()
    return data, commands


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--negative-control", action="store_true")
    parser.add_argument("--matrix", action="store_true")
    args = parser.parse_args()
    run_id = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ") + "-" + uuid.uuid4().hex[:8]
    run_folder = ROOT / "build/pilot/runs" / run_id
    target = json.loads((ROOT / "config/targets/us-eu.json").read_text())
    manifest = json.loads((ROOT / "config/build-us-eu.json").read_text())
    require_negative_controls(manifest['functions'] + manifest.get('assembly', []))
    lock, profile_path = load_profile(ROOT)
    rom, identity = audit(ROOT / target["rom_path"], target)
    if not identity["accepted"]:
        return 1
    ram = json.loads((ROOT / 'config/ram-map-us-eu.json').read_text())
    copies = ram['copies']
    validate_execution_layout(manifest['functions'], copies, ram['entries'])
    validate_symbol_definitions(manifest, copies, ram['entries'])
    if any('ram_address' in f for f in manifest['functions']):
        for copy in copies:
            validate_copy(copy, lambda off: struct.unpack_from('<I', rom, off)[0])
    commands = []
    commit = run(["git", "-C", ROOT / "toolchains/agbcc", "rev-parse", "HEAD"], commands).strip()
    if commit != manifest["compiler_source_commit"]:
        raise RuntimeError("agbcc source commit differs from the pilot pin")
    if commit != lock['compiler']['source_commit']:
        raise RuntimeError("agbcc source commit differs from the public toolchain pin")
    dirty = run(["git", "-C", ROOT / "toolchains/agbcc", "status", "--porcelain",
                 "--untracked-files=no"], commands).strip()
    if dirty:
        raise RuntimeError("agbcc tracked source has local changes")
    report = {"target": "us-eu", "reference_sha256": identity["sha256"],
              "run_id": run_id, "output_directory": str(run_folder),
              "compiler_source_commit": commit,
              "compiler_flags": manifest["compiler_flags"], "functions": [],
              "whole_rom_build_verified": False, "historical_compiler_proven": False}
    report["helper_sha256"] = {name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
                                for name in ("tools/pilot.py", "tools/project.py", "config/build-us-eu.json",
                                             "tools/toolchain.py", "tools/source_symbols.py", "tools/source_controls.py", "config/pilot-toolchain.json",
                                             "config/targets/us-eu.json", "include/irq.h",
                                             "tools/source_addresses.py", "tools/source_coverage.py", "tools/ram_copies.py", "tools/header_snapshots.py",
                                             "config/ram-map-us-eu.json")}
    report['helper_sha256'].update({str(header.relative_to(ROOT)): hashlib.sha256(header.read_bytes()).hexdigest()
                                    for header in (ROOT / 'include').rglob('*.h')})
    if profile_path:
        report['helper_sha256'][str(profile_path)] = hashlib.sha256((ROOT / profile_path).read_bytes()).hexdigest()
    report["host_clang"] = run(["xcrun", "clang", "--version"], commands).strip()
    verify_native(ROOT, lock, report['host_clang'])
    selected_ids = {compiler_selection(f, manifest['compiler_flags'])['compiler_id']
                    for f in manifest['functions']}
    report['compiler_profiles'] = {'agbcc': {'pin': 'config/pilot-toolchain.json',
                                            'compiler': lock['compiler']}}
    if 'agbcc_arm' in selected_ids:
        arm_lock, arm_profile = load_profile(ROOT, ARM_PIN, ARM_PROFILE)
        if arm_lock['compiler']['source_commit'] != commit:
            raise RuntimeError('ARM compiler source differs from the checked source pin')
        verify_native(ROOT, arm_lock, report['host_clang'])
        report['helper_sha256'][str(ARM_PIN)] = hashlib.sha256((ROOT / ARM_PIN).read_bytes()).hexdigest()
        if arm_profile:
            report['helper_sha256'][str(arm_profile)] = hashlib.sha256((ROOT / arm_profile).read_bytes()).hexdigest()
        lock = {**lock, 'native_tool_sha256': {**lock['native_tool_sha256'], **arm_lock['native_tool_sha256']}}
        report['compiler_profiles']['agbcc_arm'] = {'pin': str(ARM_PIN), 'compiler': arm_lock['compiler']}
    gcc302_locks = []
    for compiler_id, pin, local, setup in (
            ('gcc302', GCC302_PIN, GCC302_PROFILE, 'tools/setup_gcc302.py'),
            ('gcc302_hwi32', GCC302_HWI32_PIN, GCC302_HWI32_PROFILE,
             'tools/setup_gcc302_hwi32.py')):
        if compiler_id not in selected_ids:
            continue
        gcc302_lock, gcc302_profile = load_profile(ROOT, pin, local)
        verify_native(ROOT, gcc302_lock, report['host_clang'])
        verify_gcc302_source(ROOT, gcc302_lock)
        gcc302_locks.append(gcc302_lock)
        for path in (pin, Path(setup), Path('tools/setup_gcc302.py'),
                     Path(gcc302_lock['compiler']['compatibility_patch'])):
            report['helper_sha256'][str(path)] = hashlib.sha256((ROOT / path).read_bytes()).hexdigest()
        if gcc302_profile:
            report['helper_sha256'][str(gcc302_profile)] = hashlib.sha256((ROOT / gcc302_profile).read_bytes()).hexdigest()
        lock = {**lock, 'native_tool_sha256': {**lock['native_tool_sha256'], **gcc302_lock['native_tool_sha256']}}
        report['compiler_profiles'][compiler_id] = {'pin': str(pin), 'compiler': gcc302_lock['compiler']}
    selected_assembler_ids = {assembler_selection(f)['assembler_id'] for f in manifest['functions']}
    report['assembler_profiles'] = {'binutils': {'pin': 'config/pilot-toolchain.json',
                                                'object_abi_flags': modern_assembler_abi_flags()}}
    binutils2101_lock = None
    if 'binutils2101' in selected_assembler_ids:
        binutils2101_lock, local = load_profile(ROOT, BINUTILS2101_PIN, BINUTILS2101_PROFILE)
        verify_native(ROOT, binutils2101_lock, report['host_clang'])
        verify_binutils2101_source(ROOT, binutils2101_lock)
        for path in (BINUTILS2101_PIN, Path('tools/setup_binutils2101.py'),
                     Path('tools/setup_gcc302.py'),
                     Path(binutils2101_lock['assembler']['compatibility_patch'])):
            report['helper_sha256'][str(path)] = hashlib.sha256((ROOT / path).read_bytes()).hexdigest()
        if local:
            report['helper_sha256'][str(local)] = hashlib.sha256((ROOT / local).read_bytes()).hexdigest()
        lock = {**lock, 'native_tool_sha256': {**lock['native_tool_sha256'], **binutils2101_lock['native_tool_sha256']}}
        report['assembler_profiles']['binutils2101'] = {'pin': str(BINUTILS2101_PIN),
                                                        'assembler': binutils2101_lock['assembler']}
    for name in lock['native_tool_sha256']:
        path = ROOT / name
        report.setdefault("tool_sha256", {})[name] = hashlib.sha256(path.read_bytes()).hexdigest()
    for function in manifest["functions"] + manifest.get('assembly', []):
        name = function["name"]
        source = ROOT / function["source"]
        folder = run_folder / name
        folder.mkdir(parents=True, exist_ok=True)
        snapshot = folder / "source.c"
        snapshot.write_bytes(source.read_bytes())
        is_c = function.get('kind', 'compiled_c') == 'compiled_c'
        data, compile_commands = (compile_function(function, snapshot, folder, manifest["compiler_flags"])
                                  if is_c else assemble_glue(function, snapshot, folder))
        expected = rom[function["rom_offset"]:function["rom_offset"] + function["size"]]
        (folder / 'expected.bin').write_bytes(expected)
        (folder / 'candidate.bin').write_bytes(data)
        result = compare_bytes(expected, data)
        result['compiled_c_bytes'], result['assembly_glue_bytes'] = byte_counts(function)
        address = execution_address(function, copies) if is_c else 0x08000000 + function['rom_offset']
        result.update({**function, "address": f"{address:#010x}",
                       'rom_address': f"{0x08000000 + function['rom_offset']:#010x}",
                       "source_sha256": hashlib.sha256(snapshot.read_bytes()).hexdigest(),
                       "commands": compile_commands, "expected_sha256": hashlib.sha256(expected).hexdigest()})
        if is_c:
            selection = compiler_selection(function, manifest['compiler_flags'])
            result.update({'compiler_id': selection['compiler_id'], 'compiler_flags': selection['flags']})
            result['assembler_id'] = assembler_selection(function)['assembler_id']
        if args.matrix and is_c:
            result["optimization_trials"] = []
            for flag in ("-O0", "-O1", "-O2", "-O3", "-Os"):
                trial_flags = optimization_flags(selection['flags'], flag)
                trial_function = {**function, 'compiler_flags': trial_flags}
                trial_data, trial_commands = compile_function(
                    trial_function, snapshot, folder / flag[1:], trial_flags)
                trial = compare_bytes(expected, trial_data)
                trial.update({"flags": trial_flags, "commands": trial_commands})
                result["optimization_trials"].append(trial)
        if args.negative_control and 'negative_control' in function:
            control_folder = folder / 'negative-control'
            control_folder.mkdir()
            changed = control_folder / ('changed.c' if is_c else 'changed.s')
            changed.write_text(mutate(snapshot.read_text(), function['negative_control']))
            control_data, control_commands = (compile_function(function, changed, control_folder, manifest['compiler_flags'])
                                             if is_c else assemble_glue(function, changed, control_folder))
            (control_folder / 'candidate.bin').write_bytes(control_data)
            control = compare_bytes(expected, control_data)
            control.update({'rejected': not control['identical'], 'commands': control_commands,
                            'source_edit': function['negative_control'],
                            'source_sha256': hashlib.sha256(changed.read_bytes()).hexdigest()})
            result['negative_control'] = control
        if args.negative_control and function.get('inline_glue'):
            spec = function['inline_glue']
            control_folder = folder / 'inline-glue-control'
            control_folder.mkdir()
            header_name = Path(spec['source']).relative_to('include').as_posix()
            original_header = (folder / 'include' / header_name).read_text()
            changed_header = mutate(original_header, spec['negative_control'])
            control_data, control_commands = compile_function(
                function, snapshot, control_folder, manifest['compiler_flags'],
                header_overrides={header_name: changed_header})
            (control_folder / 'candidate.bin').write_bytes(control_data)
            control = compare_bytes(expected, control_data)
            control.update({'rejected': not control['identical'], 'commands': control_commands,
                            'source_edit': spec['negative_control'],
                            'header': spec['source'],
                            'source_sha256': hashlib.sha256(changed_header.encode()).hexdigest()})
            result['inline_glue_control'] = control
        verified = verified_comparison(result, controls_compiled=args.negative_control)
        result['source_reconstruction_verified'] = verified and is_c
        result['assembly_glue_verified'] = verified and not is_c
        result['inline_glue_verified'] = verified and bool(inline_glue(function))
        report["functions"].append(result)
        print(f"{name}: {'MATCH' if result['identical'] else 'MISMATCH'} ({len(data)} / {len(expected)} bytes)")
    report["matched_functions"] = sum(r["source_reconstruction_verified"] for r in report["functions"])
    report["matched_bytes_including_pools_and_padding"] = sum(r['compiled_c_bytes'] for r in report["functions"] if r["source_reconstruction_verified"])
    report['assembly_glue_bytes'] = sum(r['assembly_glue_bytes'] for r in report['functions']
                                      if verified_comparison(r, controls_compiled=args.negative_control))
    accepted = bool(args.negative_control) and all(
        verified_comparison(r, controls_compiled=args.negative_control)
        for r in report['functions'])
    if args.negative_control:
        function = manifest["functions"][0]
        folder = run_folder / "negative-control"
        folder.mkdir(parents=True, exist_ok=True)
        original = (ROOT / function["source"]).read_text()
        if "= value;" not in original:
            raise RuntimeError("Negative control edit no longer applies")
        source = folder / "changed.c"
        source.write_text(original.replace("= value;", "= value + 1;"))
        data, compile_commands = compile_function(function, source, folder, manifest["compiler_flags"])
        expected = rom[function["rom_offset"]:function["rom_offset"] + function["size"]]
        control = compare_bytes(expected, data)
        control.update({"source_edit": "store value + 1 instead of value", "commands": compile_commands,
                        "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
                        "rejected": not control["identical"]})
        report["negative_control"] = control
        accepted = accepted and control["rejected"]
        print(f"Changed-source negative control: {'REJECTED' if control['rejected'] else 'UNEXPECTED MATCH'}")
    if any(hashlib.sha256((ROOT / name).read_bytes()).hexdigest() != digest
           for name, digest in report['helper_sha256'].items()):
        raise ValueError('Source helpers changed during the run; retry with stable inputs')
    verify_native(ROOT, lock, report['host_clang'])
    for gcc302_lock in gcc302_locks:
        verify_gcc302_source(ROOT, gcc302_lock)
    if binutils2101_lock:
        verify_binutils2101_source(ROOT, binutils2101_lock)
    report["accepted"] = accepted
    (run_folder / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    write_report("pilot", report)
    return 0 if accepted else 1


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError, RuntimeError) as error:
        print(error, file=sys.stderr)
        sys.exit(2)
