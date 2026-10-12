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

from elftools.elf.elffile import ELFFile
from project import ROOT, audit, compare_bytes, write_report
from toolchain import load_profile, verify_native


def run(command, commands):
    commands.append([str(arg) for arg in command])
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode:
        raise RuntimeError(f"Command failed: {commands[-1]}\n{result.stderr[-6000:]}")
    return result.stdout


def compile_function(function, source, folder, flags):
    folder.mkdir(parents=True, exist_ok=True)
    commands = []
    header_folder = folder / "include"
    header_folder.mkdir(exist_ok=True)
    for header in (ROOT / "include").glob("*.h"):
        (header_folder / header.name).write_bytes(header.read_bytes())
    preprocessed = folder / "source.i"
    assembly = folder / "source.s"
    obj = folder / "source.o"
    linked = folder / "linked.elf"
    address = 0x08000000 + function["rom_offset"]
    run(["xcrun", "clang", "--target=arm-none-eabi", "-E", "-P", "-undef",
         "-nostdinc", "-std=gnu89", "-I", header_folder, source, "-o", preprocessed], commands)
    run([ROOT / "toolchains/agbcc/gcc/agbcc", *flags, preprocessed, "-o", assembly], commands)
    run([ROOT / "toolchains/binutils/bin/arm-none-eabi-as", "-mcpu=arm7tdmi",
         "-mthumb", "--no-pad-sections", assembly, "-o", obj], commands)
    # Mark external function addresses as Thumb, so the linker does not invent
    # ARM interworking veneers for absolute ROM symbols.
    externs = folder / "externs.s"
    declarations = []
    for name, value in function.get("symbols", {}).items():
        if name in ("irq_noop", "frame_update", "_call_via_r0"):
            declarations += [f".global {name}", f".type {name}, %function",
                             f".thumb_set {name}, {value}"]
        else:
            declarations += [f".global {name}", f".set {name}, {value}"]
    externs.write_text("\n".join(declarations) + "\n")
    extern_obj = folder / "externs.o"
    run([ROOT / "toolchains/binutils/bin/arm-none-eabi-as", externs, "-o", extern_obj], commands)
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
    return data, commands


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--negative-control", action="store_true")
    parser.add_argument("--matrix", action="store_true")
    args = parser.parse_args()
    run_id = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ") + "-" + uuid.uuid4().hex[:8]
    run_folder = ROOT / "build/pilot/runs" / run_id
    target = json.loads((ROOT / "config/targets/us-eu.json").read_text())
    manifest = json.loads((ROOT / "pilot/manifest.json").read_text())
    lock, profile_path = load_profile(ROOT)
    rom, identity = audit(ROOT / target["rom_path"], target)
    if not identity["accepted"]:
        return 1
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
                                for name in ("tools/pilot.py", "tools/project.py", "pilot/manifest.json",
                                             "tools/toolchain.py", "config/pilot-toolchain.json",
                                             "config/targets/us-eu.json", "include/irq.h")}
    if profile_path:
        report['helper_sha256'][str(profile_path)] = hashlib.sha256((ROOT / profile_path).read_bytes()).hexdigest()
    report["host_clang"] = run(["xcrun", "clang", "--version"], commands).strip()
    verify_native(ROOT, lock, report['host_clang'])
    for name in lock['native_tool_sha256']:
        path = ROOT / name
        report.setdefault("tool_sha256", {})[name] = hashlib.sha256(path.read_bytes()).hexdigest()
    for function in manifest["functions"]:
        name = function["name"]
        source = ROOT / function.get("source", "pilot/candidates/" + name + ".c")
        folder = run_folder / name
        folder.mkdir(parents=True, exist_ok=True)
        snapshot = folder / "source.c"
        snapshot.write_bytes(source.read_bytes())
        data, compile_commands = compile_function(function, snapshot, folder, manifest["compiler_flags"])
        expected = rom[function["rom_offset"]:function["rom_offset"] + function["size"]]
        result = compare_bytes(expected, data)
        # This result is backed by source compilation and a checked linked extent.
        result["source_reconstruction_verified"] = result["identical"]
        result.update({**function, "address": f"{0x08000000 + function['rom_offset']:#010x}",
                       "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
                       "commands": compile_commands, "expected_sha256": hashlib.sha256(expected).hexdigest()})
        if args.matrix:
            result["optimization_trials"] = []
            for flag in ("-O0", "-O1", "-O2", "-O3", "-Os"):
                trial_data, trial_commands = compile_function(
                    function, snapshot, folder / flag[1:], [flag, "-mthumb-interwork"])
                trial = compare_bytes(expected, trial_data)
                trial.update({"flags": [flag, "-mthumb-interwork"], "commands": trial_commands})
                result["optimization_trials"].append(trial)
        report["functions"].append(result)
        print(f"{name}: {'MATCH' if result['identical'] else 'MISMATCH'} ({len(data)} / {len(expected)} bytes)")
    report["matched_functions"] = sum(r["identical"] for r in report["functions"])
    report["matched_bytes_including_pools_and_padding"] = sum(r["size"] for r in report["functions"] if r["identical"])
    accepted = report["matched_functions"] == len(manifest["functions"])
    if args.negative_control:
        function = manifest["functions"][0]
        folder = run_folder / "negative-control"
        folder.mkdir(parents=True, exist_ok=True)
        original = (ROOT / "pilot/candidates" / (function["name"] + ".c")).read_text()
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
    report["accepted"] = accepted
    (run_folder / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    write_report("pilot", report)
    return 0 if accepted else 1


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, RuntimeError) as error:
        print(error, file=sys.stderr)
        sys.exit(2)
