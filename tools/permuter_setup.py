#!/usr/bin/env python3
"""Private decomp-permuter jobs using the project's pinned compilation context.

Scores guide searches only. Validation compares the complete fixed ROM extent;
source, interface, controls and publication gates remain separate.

Usage: setup ROW creates analysis/permuter/ROW. Run its run.sh for a local
8-worker search with TMPDIR, stack and branch scoring set. Existing jobs are
never overwritten; use --output for a fresh rerun. validate JOB OUTPUT_DIR
recompiles saved full-context source and checks every reference byte.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
import time

from elftools.elf.elffile import ELFFile
from header_snapshots import (snapshot_headers, retained_source, verify_snapshot_inputs,
                              verify_preprocessor_dependencies)
from project import ROOT, compare_bytes
from project_header_store import write_header_override
from source_addresses import execution_address
from source_symbols import declarations
from toolchain import (compiler_selection, assembler_selection, load_profile,
                       verify_native)

UPSTREAM = Path('toolchains/decomp-permuter')
UPSTREAM_COMMIT = '8556c81d80d1c1af98a858c8f4dc951357f29139'
SAFE_WEIGHTS = {'perm_temp_for_expr': 100, 'perm_expand_expr': 20,
                'perm_reorder_decls': 10, 'perm_split_assignment': 10,
                'perm_compound_assignment': 5, 'perm_reverse_cond': 5}
MAX_SOURCE_BYTES = 2 * 1024 * 1024


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def record(path, root=ROOT):
    path = Path(path)
    return {'path': path.relative_to(root).as_posix(), 'sha256': digest(path),
            'bytes': path.stat().st_size}


def write_json(path, value):
    Path(path).write_text(json.dumps(value, indent=2) + '\n')


def plain_path(path):
    path = Path(os.path.abspath(path))
    if path.resolve() != path:
        raise ValueError('Symlink or traversal through a symlink is forbidden')
    return path


def private_path(path, root=ROOT):
    raw = Path(path)
    if '..' in raw.parts:
        raise ValueError('Output traversal is forbidden')
    path = plain_path(raw if raw.is_absolute() else root / raw)
    base = plain_path(root / 'analysis/permuter')
    if path == base or base not in path.parents:
        raise ValueError('Output must be below analysis/permuter')
    relative = path.relative_to(root).as_posix()
    if subprocess.check_output(['git', 'ls-files', '--', relative], cwd=root):
        raise ValueError('Generated path is tracked')
    if subprocess.run(['git', 'check-ignore', '-q', '--', relative], cwd=root).returncode:
        raise ValueError('Generated path must be ignored')
    return path


def run(argv, commands, cwd=ROOT):
    args = [str(x) for x in argv]
    result = subprocess.run(args, cwd=cwd, text=True, capture_output=True)
    commands.append({'argv': args, 'returncode': result.returncode,
                     'stdout': result.stdout, 'stderr': result.stderr})
    if result.returncode:
        raise RuntimeError(result.stderr[-6000:] or 'Command failed: ' + args[0])
    return result.stdout


def parser_modules(root=ROOT):
    upstream = root / UPSTREAM
    if str(upstream) not in sys.path:
        sys.path.insert(0, str(upstream))
    from src import ast_util
    from perm_pycparser import c_ast
    return ast_util, c_ast


def source_contract(source, name, root=ROOT):
    """Preserve all external declarations, the target API, and existing asm.

    This is a structural search boundary, not proof of C semantic equivalence.
    """
    if len(source.encode()) > MAX_SOURCE_BYTES:
        raise ValueError('Candidate source exceeds limit')
    if re.search(r'^\s*#\s*(include|include_next|define|undef|if|line)\b', source, re.M):
        raise ValueError('Candidate must be the retained preprocessed context')
    util, ca = parser_modules(root)
    ast = util.parse_c(source)
    functions = [n for n in ast.ext if isinstance(n, ca.FuncDef)]
    targets = [n for n in functions if n.decl.name == name]
    if len(targets) != 1 or any(n.decl.name != name and 'inline' not in n.decl.funcspec
                                for n in functions):
        raise ValueError('Only the requested function and existing inline providers are allowed')
    target = targets[0]
    outer = [util.to_c_raw(n) for n in ast.ext if n is not target]
    asm = []
    bindings = []

    class Visitor(ca.NodeVisitor):
        def visit_Asm(self, node):
            asm.append(util.to_c_raw(node))

        def visit_Decl(self, node):
            if node.asmlabel:
                bindings.append([node.name, util.to_c_raw(node.asmlabel)])
            self.generic_visit(node)

    Visitor().visit(target.body)
    return {'external': outer, 'function': util.to_c_raw(target.decl),
            'local_asm': asm, 'register_bindings': sorted(bindings)}


def check_candidate(source, job, root=ROOT):
    if source_contract(source, job['function']['name'], root) != job['source_contract']:
        raise ValueError('Candidate changed an API, global/inline context, asm or register binding')
    # No assembly payload or file-backed code may enter a C search candidate.
    if re.search(r'\.(incbin|include)\b', source):
        raise ValueError('Candidate assembly may not include external payloads')


def verify_records(records, root=ROOT):
    for item in records:
        path = plain_path(root / item['path'])
        if not path.is_file() or path.stat().st_size != item['bytes'] or digest(path) != item['sha256']:
            raise ValueError('Pinned input changed: ' + item['path'])


def check_upstream(root=ROOT):
    folder = root / UPSTREAM
    commit = subprocess.check_output(['git', '-C', str(folder), 'rev-parse', 'HEAD'], text=True).strip()
    if commit != UPSTREAM_COMMIT or subprocess.check_output(
            ['git', '-C', str(folder), 'status', '--porcelain', '--untracked-files=no']):
        raise ValueError('Permuter source differs from the reviewed upstream revision')
    return commit


def checked_gate(path):
    gate = json.loads(Path(path).read_text())
    if (gate.get('status') != 'PASS_MATCHED_THUMB_GATE' or gate.get('matched_score') != 0
            or gate.get('changed_control_score', 0) <= 0 or not gate.get('full_bytes_identical')
            or gate.get('actual_instruction_rows', 0) < 1
            or gate.get('stack_differences') is not True or gate.get('ign_branch_targets') is not False):
        raise ValueError('A passing nonempty Thumb positive/control gate is required')
    return gate


def text_bytes(path, address, name, mode, maximum=None):
    with Path(path).open('rb') as stream:
        elf = ELFFile(stream)
        allocated = [s for s in elf.iter_sections() if s['sh_flags'] & 2 and s['sh_size']]
        if (elf['e_type'] != 'ET_EXEC' or elf['e_machine'] != 'EM_ARM'
                or len(allocated) != 1 or allocated[0].name != '.text'
                or allocated[0]['sh_addr'] != address):
            raise ValueError('Candidate ELF has the wrong architecture, sections or address')
        if any(s['sh_type'] in ('SHT_REL', 'SHT_RELA') and s['sh_size'] for s in elf.iter_sections()):
            raise ValueError('Unresolved candidate relocation')
        symbols = elf.get_section_by_name('.symtab')
        functions = [s for s in symbols.iter_symbols() if s['st_info']['type'] == 'STT_FUNC' and s['st_size']]
        if len(functions) != 1 or functions[0].name != name or functions[0]['st_value'] != address + (mode == 'Thumb'):
            raise ValueError('Candidate emits another function or wrong instruction mode')
        data = allocated[0].data()
        if not data or (maximum is not None and len(data) > maximum):
            raise ValueError('Candidate extent is empty or exceeds search limit')
        return data


def validate_row_selection(function, root=ROOT):
    inventory = json.loads((root / 'assets/rom-inventory.json').read_text())
    rows = [r for r in inventory['rows'] if r['rom_offset'] == function['rom_offset']]
    if len(rows) != 1:
        raise ValueError('Function needs one current inventory row')
    row = rows[0]
    if function.get('mode', 'Thumb') != row['mode']:
        raise ValueError('Wrong mode for current inventory row')
    ram = json.loads((root / 'config/ram-map-us-eu.json').read_text())
    address = execution_address(function, ram['copies'], ram['entries'])
    if address not in row['runtime_addresses']:
        raise ValueError('Wrong execution/copy address for current inventory row')
    accepted = json.loads((root / 'config/build-us-eu.json').read_text())
    owners = [f for f in accepted['functions'] if f['rom_offset'] == function['rom_offset']]
    # The sole currently admitted exceptional unowned Thumb backend is explicit.
    expected = (compiler_selection(owners[0], accepted['compiler_flags'])['compiler_id'] if owners
                else {0x49968: 'gcc302'}.get(function['rom_offset'], 'agbcc_arm' if row['mode'] == 'ARM' else 'agbcc'))
    selected = compiler_selection(function, accepted['compiler_flags'])
    if selected['compiler_id'] != expected:
        raise ValueError('Wrong compiler assignment for this row; use its qualified pinned backend')
    if function['size'] < row.get('decoded_instruction_bytes', 0) + row.get('referenced_literal_bytes', 0):
        raise ValueError('Reference extent truncates current instruction/literal coverage')
    return row


def profile_context(selection, root=ROOT):
    profile, local = load_profile(root, selection['pin'], selection['profile'])
    files = [root / selection['pin']]
    if local is not None:
        files.append(root / local)
    return profile, files


def reference_assembly(name, mode, reference):
    """Emit target-only data using directives shared by both pinned assemblers.

    Legacy GNU as lacks .syntax and .incbin. Numeric bytes need neither and
    preserve the complete reference extent without instruction interpretation.
    Candidate compiler assembly still uses its original selected assembler.
    """
    if not isinstance(name, str) or not re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', name):
        raise ValueError('Invalid reference function name')
    if mode not in ('Thumb', 'ARM'):
        raise ValueError('Unsupported reference instruction mode')
    if not isinstance(reference, (bytes, bytearray)) or not reference:
        raise ValueError('Reference must contain bytes')
    lines = ['.text', '.global ' + name, '.type ' + name + ',%function']
    lines += ['.thumb', '.thumb_func'] if mode == 'Thumb' else ['.arm']
    lines.append(name + ':')
    for offset in range(0, len(reference), 16):
        lines.append('.byte ' + ','.join(str(byte) for byte in reference[offset:offset + 16]))
    lines.append('.size ' + name + ',.-' + name)
    return '\n'.join(lines) + '\n'


def setup(function, source, output, gate_path, overrides=None, root=ROOT, metadata_path=None):
    """Snapshot once; generate no target/code artifacts outside the private job."""
    output = private_path(output, root)
    if output.exists():
        raise ValueError('A fresh job directory is required')
    source = plain_path(source)
    gate_path = plain_path(gate_path)
    checked_gate(gate_path)
    check_upstream(root)
    row = validate_row_selection(function, root)
    if metadata_path is not None:
        old_snapshot = plain_path(metadata_path).parent / 'normal/header-snapshot.json'
        if old_snapshot.is_file():
            old_headers = json.loads(old_snapshot.read_text())['headers']
            for name, expected in old_headers.items():
                current = root / 'include' / name
                chosen = plain_path((overrides or {}).get(name, current))
                if not chosen.is_file() or digest(chosen) != expected:
                    raise ValueError('Header context changed; required --header-override ' + name + '=' + str(old_snapshot.parent / 'include' / name))
    selected = compiler_selection(function, ['-O2', '-mthumb-interwork'])
    assembler = assembler_selection(function)
    profile, profile_files = profile_context(selected, root)
    host = subprocess.check_output(['xcrun', 'clang', '--version'], text=True).strip()
    verify_native(root, profile, host)
    assembler_profile, assembler_profile_files = profile_context(assembler, root)
    verify_native(root, assembler_profile, host)
    if not re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', function['name']):
        raise ValueError('Invalid function name')
    output.mkdir(parents=True)
    (output / 'tmp').mkdir()
    commands = []
    context = output / 'context'
    headers = snapshot_headers(source, context / 'include', root / 'include',
                               project_header_store=output / 'header-store')
    for name, path in (overrides or {}).items():
        if name not in headers['headers']:
            raise ValueError('Private override is outside retained header closure')
        data = plain_path(path).read_bytes()
        write_header_override(context / 'include' / name, data.decode())
        headers['headers'][name] = hashlib.sha256(data).hexdigest()
    write_json(context / 'header-snapshot.json', headers)
    original = retained_source(headers, context / 'include')
    dep = context / 'preprocessor.d'
    run(['xcrun', 'clang', '--target=arm-none-eabi', '-E', '-P', '-undef', '-nostdinc',
         '-std=gnu89', '-MD', '-MF', dep, '-MT', 'snapshot', '-I', context / 'include',
         original, '-o', output / 'base.c'], commands, root)
    verify_snapshot_inputs(headers, context / 'include')
    headers['preprocessor_dependencies'] = verify_preprocessor_dependencies(headers, context / 'include', dep)
    write_json(context / 'header-snapshot.json', headers)
    base = (output / 'base.c').read_text()
    contract = source_contract(base, function['name'], root)
    if re.search(r'\.(incbin|include)\b', base):
        raise ValueError('Base C contains an external assembly payload')
    target = json.loads((root / 'config/targets/us-eu.json').read_text())
    rom = (root / target['rom_path']).read_bytes()
    if hashlib.sha256(rom).hexdigest() != target['sha256']:
        raise ValueError('Reference ROM identity changed')
    offset, size = function['rom_offset'], function['size']
    if not isinstance(offset, int) or not isinstance(size, int) or offset < 0 or size <= 0 or offset + size > len(rom):
        raise ValueError('Invalid full reference extent')
    ram = json.loads((root / 'config/ram-map-us-eu.json').read_text())
    address = execution_address(function, ram['copies'], ram['entries'])
    reference = rom[offset:offset + size]
    (output / 'reference.bin').write_bytes(reference)
    mode = function.get('mode', 'Thumb')
    (output / 'target.s').write_text(reference_assembly(function['name'], mode, reference))
    (output / 'function.ld').write_text(f'SECTIONS {{ .text {address:#x} : {{ *(.text) . = ALIGN(4); }} = 0 }}\n')
    # The target itself has the exact reference size, independent of candidate alignment.
    (output / 'target.ld').write_text(f'SECTIONS {{ .text {address:#x} : {{ *(.text) }} }}\n')
    run([root / assembler['executable'], *assembler['source_flags'], output / 'target.s', '-o', output / 'target-rel.o'], commands, root)
    run([root / 'toolchains/binutils/bin/arm-none-eabi-ld', '-T', output / 'target.ld',
         '--entry=' + function['name'], output / 'target-rel.o', '-o', output / 'target.o'], commands, root)
    if text_bytes(output / 'target.o', address, function['name'], mode) != reference:
        raise ValueError('Generated target differs from fixed reference bytes')
    (output / 'target-rel.o').unlink()
    (output / 'externs.s').write_text('\n'.join(declarations(function.get('symbols', {}), function.get('thumb_symbols', ()))) + '\n')
    run([root / assembler['executable'], *assembler['extern_flags'], output / 'externs.s', '-o', output / 'externs.o'], commands, root)
    objdump = [str(root / 'toolchains/binutils/bin/arm-none-eabi-objdump'), '-Drz', '-j', '.text']
    if mode == 'Thumb':
        objdump += ['-M', 'force-thumb']
    # Explicit zeros avoid inheriting upstream fake-use and contract mutation passes.
    sys.path.insert(0, str(root / UPSTREAM))
    from src.helpers import get_default_randomization_weights
    weights = {k: SAFE_WEIGHTS.get(k, 0) for k in get_default_randomization_weights('gcc')}
    settings = 'func_name = ' + json.dumps(function['name']) + '\ncompiler_type = "gcc"\nobjdump_command = ' + json.dumps(shlex.join(objdump)) + '\n\n[weight_overrides]\n'
    settings += ''.join(f'{k} = {v}\n' for k, v in sorted(weights.items()))
    (output / 'settings.toml').write_text(settings)
    python = root / 'toolchains/search-venv/bin/python'
    if not python.is_file():
        raise ValueError('Install the isolated search Python environment first')
    compile_cmd = [str(python), '-B', str(root / 'tools/permuter_setup.py'), 'compile', str(output)]
    (output / 'compile.sh').write_text('#!/bin/sh\nset -eu\nexec ' + shlex.join(compile_cmd) + ' "$@"\n')
    (output / 'compile.sh').chmod(0o755)
    launcher = [str(python), '-B', str(root / UPSTREAM / 'permuter.py'), str(output),
                '--stack-diffs', '--no-ignore-branch-targets', '--best-only', '--better-only', '--stop-on-zero', '-j', '8']
    (output / 'run.sh').write_text('#!/bin/sh\nset -eu\ncd ' + shlex.quote(str(output)) + '\nexport TMPDIR=' + shlex.quote(str(output / 'tmp')) + '\nexec ' + shlex.join(launcher) + '\n')
    (output / 'run.sh').chmod(0o755)
    write_json(output / 'function.json', function)
    files = {source, gate_path, root / 'tools/permuter_setup.py', root / 'config/targets/us-eu.json', root / 'config/ram-map-us-eu.json'}
    files.update(profile_files + assembler_profile_files)
    files.update(root / p for p in profile['native_tool_sha256'])
    files.update(root / p for p in assembler_profile['native_tool_sha256'])
    files.update((root / assembler['executable'],
                  root / 'toolchains/binutils/bin/arm-none-eabi-objdump', root / 'toolchains/binutils/bin/arm-none-eabi-ld',
                  root / 'tools/triage.py'))
    if metadata_path is not None:
        files.add(plain_path(metadata_path))
    files.update(root / 'tools' / n for n in ('header_snapshots.py', 'project_header_store.py', 'toolchain.py', 'source_addresses.py', 'source_symbols.py', 'project.py'))
    files.update(context / 'include' / h for h in headers['headers'])
    files.update(root / 'include' / h for h in headers['headers'] if h not in (overrides or {}))
    files.update(plain_path(p) for p in (overrides or {}).values())
    files.update(p for p in (context / 'source-inputs').rglob('*') if p.is_file())
    files.update(source.parent / h for h in headers['source_bundle']['source_local_headers'])
    files.update(output / n for n in ('base.c', 'target.o', 'reference.bin', 'externs.o', 'function.ld', 'settings.toml', 'compile.sh', 'run.sh', 'function.json', 'context/header-snapshot.json'))
    upstream_files = subprocess.check_output(['git', '-C', str(root / UPSTREAM), 'ls-files'], text=True).splitlines()
    files.update(root / UPSTREAM / p for p in upstream_files if p.endswith(('.py', '.toml')))
    verify_native(root, profile, host)
    job = {'schema': 1, 'status': 'READY_FOR_LOCAL_SEARCH', 'function': function,
           'execution_address': address, 'row_selection': {k: row[k] for k in ('rom_offset', 'mode', 'runtime_addresses', 'size')}, 'mode': mode, 'compiler': selected['compiler_id'],
           'compiler_path': selected['executable'].as_posix(), 'compiler_flags': selected['flags'],
           'assembler_path': assembler['executable'].as_posix(), 'assembler_flags': assembler['source_flags'],
           'profile': profile, 'host_clang': host, 'reference_sha256': hashlib.sha256(reference).hexdigest(),
           'reference_rom_sha256': target['sha256'], 'upstream_commit': UPSTREAM_COMMIT,
           'gate': record(gate_path, root), 'source_contract': contract, 'safe_weights_reviewed': True,
           'weights': weights, 'immutable_inputs': [record(p, root) for p in sorted(files)],
           'objdump_command': objdump, 'stack_diffs_required': True, 'branch_targets_required': True,
           'full_byte_validation_required': True, 'scope': 'Search hint only; forced disassembly also interprets literal/alignment bytes. No acceptance or source coverage.'}
    write_json(output / 'setup-commands.json', commands)
    write_json(output / 'setup.json', job)
    return output / 'setup.json'


def load_job(directory, root=ROOT):
    directory = private_path(directory, root)
    job = json.loads((directory / 'setup.json').read_text())
    if job.get('schema') != 1 or job.get('status') != 'READY_FOR_LOCAL_SEARCH':
        raise ValueError('Unsupported job manifest')
    verify_records(job['immutable_inputs'], root)
    if json.loads((directory / 'function.json').read_text()) != job['function']:
        raise ValueError('Job function metadata changed')
    if source_contract((directory / 'base.c').read_text(), job['function']['name'], root) != job['source_contract']:
        raise ValueError('Job source contract changed')
    row = validate_row_selection(job['function'], root)
    if {k: row[k] for k in job['row_selection']} != job['row_selection']:
        raise ValueError('Selected inventory row mode/address/extent changed')
    selected = compiler_selection(job['function'], job['compiler_flags'])
    if (selected['executable'].as_posix() != job['compiler_path'] or selected['flags'] != job['compiler_flags']
            or selected['compiler_id'] != job['compiler']):
        raise ValueError('Wrong compiler or flags in job')
    host = subprocess.check_output(['xcrun', 'clang', '--version'], text=True).strip()
    verify_native(root, job['profile'], host)
    return directory, job


def compile_candidate(directory, source, destination, *, retained=None, root=ROOT):
    directory, job = load_job(directory, root)
    source = private_path(source, root)
    destination = private_path(destination, root)
    protected = {plain_path(root / p['path']) for p in job['immutable_inputs']} | {directory / 'setup.json'}
    private_path(directory / 'tmp', root)
    if source in {directory / 'target.o', directory / 'reference.bin'} or destination in protected or destination == source:
        raise ValueError('Candidate output overlaps protected inputs or target')
    if destination.exists() and (destination.stat().st_size or destination.stat().st_nlink != 1):
        raise ValueError('Candidate output must be fresh or empty')
    body = source.read_text()
    check_candidate(body, job, root)
    commands = []
    with tempfile.TemporaryDirectory(prefix='compile-', dir=directory / 'tmp') as temporary:
        work = Path(temporary)
        (work / 'source.c').write_text(body)
        run(['xcrun', 'clang', '--target=arm-none-eabi', '-E', '-P', '-undef', '-nostdinc',
             '-std=gnu89', work / 'source.c', '-o', work / 'source.i'], commands, root)
        run([root / job['compiler_path'], *job['compiler_flags'], work / 'source.i', '-o', work / 'source.s'], commands, root)
        run([root / job['assembler_path'], *job['assembler_flags'], work / 'source.s', '-o', work / 'source.o'], commands, root)
        with (work / 'source.o').open('rb') as stream:
            elf = ELFFile(stream)
            if any(s['sh_flags'] & 2 and s['sh_size'] and s.name != '.text' for s in elf.iter_sections()):
                raise ValueError('Unexpected allocated source section')
        run([root / 'toolchains/binutils/bin/arm-none-eabi-ld', '-T', directory / 'function.ld',
             '--entry=' + job['function']['name'], work / 'source.o', directory / 'externs.o',
             '-o', work / 'linked.elf'], commands, root)
        raw = text_bytes(work / 'linked.elf', job['execution_address'], job['function']['name'],
                         job['mode'], max(4096, job['function']['size'] * 8))
        verify_records(job['immutable_inputs'], root)
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(work / 'linked.elf', destination)
        if retained is not None:
            retained = private_path(retained, root)
            retained.mkdir(parents=True, exist_ok=False)
            for name in ('source.c', 'source.i', 'source.s', 'linked.elf'):
                shutil.copyfile(work / name, retained / name)
            (retained / 'candidate.bin').write_bytes(raw)
            write_json(retained / 'commands.json', commands)
        return raw


def validate(directory, candidate, output=None, root=ROOT):
    directory, job = load_job(directory, root)
    candidate = private_path(candidate, root)
    if candidate.is_dir():
        candidate = candidate / 'source.c'
    output = private_path(output or directory / ('validation-' + str(time.time_ns())), root)
    if output.exists():
        raise ValueError('Validation output must be fresh')
    result_elf = directory / 'tmp' / ('validation-' + str(time.time_ns()) + '.o')
    try:
        raw = compile_candidate(directory, candidate, result_elf, retained=output, root=root)
    finally:
        result_elf.unlink(missing_ok=True)
    target = json.loads((root / 'config/targets/us-eu.json').read_text())
    rom = (root / target['rom_path']).read_bytes()
    if hashlib.sha256(rom).hexdigest() != job['reference_rom_sha256']:
        raise ValueError('Fixed ROM changed')
    f = job['function'];comparison = compare_bytes(rom[f['rom_offset']:f['rom_offset'] + f['size']], raw)
    result = {'status': 'FULL_BYTES_MATCH_REVIEW_REQUIRED' if comparison['identical'] else 'NONMATCH',
              'comparison': comparison, 'job_manifest': record(directory / 'setup.json', root),
              'candidate_source': record(candidate, root), 'source_credit': 0,
              'scope': 'Fresh normal full-byte check only. Source/API review, strict/control and full gates remain required.'}
    write_json(output / 'result.json', result)
    return output / 'result.json'


def resolve_row(name, root=ROOT):
    from triage import resolve_row as triage_resolve_row
    resolved = triage_resolve_row(root, name)
    metadata = resolved['metadata']
    return (json.loads(metadata.read_text()), resolved['source'], metadata,
            resolved['header_overrides'])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    subs = parser.add_subparsers(dest='command', required=True)
    p = subs.add_parser('setup');p.add_argument('row', nargs='?');p.add_argument('--function');p.add_argument('--metadata', type=Path)
    p.add_argument('--source', type=Path);p.add_argument('--output', type=Path)
    p.add_argument('--gate', type=Path, default=ROOT / 'analysis/permuter/gate-frame-note-oam-20261025/assessment.json');p.add_argument('--header-override', action='append', default=[])
    p = subs.add_parser('compile');p.add_argument('job', type=Path);p.add_argument('source', type=Path);p.add_argument('-o', required=True, type=Path)
    p = subs.add_parser('validate');p.add_argument('job', type=Path);p.add_argument('candidate', type=Path);p.add_argument('--output', type=Path)
    args = parser.parse_args()
    if args.command == 'setup':
        manifest = json.loads((ROOT / 'config/build-us-eu.json').read_text())
        requested = args.row or args.function
        overrides = {}
        if args.row and args.function and args.row != args.function:
            parser.error('Use one row/function name')
        if not args.metadata and requested and not any(f['name'] == requested for f in manifest['functions']):
            function, retained, args.metadata, overrides = resolve_row(requested)
            args.source = args.source or retained
        if args.metadata:
            function = json.loads(args.metadata.read_text())
            if requested and requested != function['name']:
                rows = json.loads((ROOT / 'assets/rom-inventory.json').read_text())['rows']
                if not any(r['rom_offset'] == function['rom_offset'] and
                           (r['name'] == requested or requested.lower() == hex(r['rom_offset'])) for r in rows):
                    parser.error('Requested row/function differs from metadata')
        else:
            function = next((f for f in manifest['functions'] if f['name'] == requested), None)
            if function is None:
                parser.error('Unknown manifest function; supply explicit private metadata')
        function = dict(function);function.setdefault('compiler_flags', manifest['compiler_flags'])
        overrides.update(dict(v.split('=', 1) for v in args.header_override))
        if args.output is None:
            label = requested or function['name']
            if not re.fullmatch(r'[A-Za-z0-9_]+', label):
                parser.error('Invalid row name')
            args.output = ROOT / 'analysis/permuter' / label
        result = setup(function, args.source or ROOT / function['source'], args.output, args.gate, overrides, metadata_path=args.metadata)
    elif args.command == 'compile':
        compile_candidate(args.job, args.source, args.o);return
    else:
        result = validate(args.job, args.candidate, args.output)
    print(result)


if __name__ == '__main__':
    main()
