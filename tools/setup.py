#!/usr/bin/env python3
"""Provision pinned public tools on macOS; never download game content."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import venv

from project import ROOT
from toolchain import PIN, PROFILE, load_profile, sha, verify_native

PENDING = Path('toolchains/setup-pending.json')


def pending_profile(root, pins, host_clang):
    """Resume completed components after e.g. a later download/build fails."""
    pending = root / PENDING
    if not pending.exists():
        return {**pins, 'host_clang': host_clang}
    saved = json.loads(pending.read_text())
    fingerprints = saved.get('native_tool_sha256', {})
    if (saved.get('source_pin_sha256') != sha(root / PIN) or
            saved.get('host_clang') != host_clang or not isinstance(fingerprints, dict) or
            not set(fingerprints).issubset(pins['native_tool_sha256'])):
        raise RuntimeError('Incomplete setup belongs to different source pins or host tools')
    verify_native(root, saved, host_clang)
    return {**pins, 'native_tool_sha256': {**pins['native_tool_sha256'], **fingerprints},
            'host_clang': host_clang}


def record_completed(names, pins, host_clang):
    if not names:
        return
    pending_profile(ROOT, pins, host_clang)
    saved_path = ROOT / PENDING
    saved = json.loads(saved_path.read_text()) if saved_path.exists() else {
        'source_pin_sha256': sha(ROOT / PIN), 'host_clang': host_clang, 'native_tool_sha256': {}}
    saved['native_tool_sha256'].update({name: sha(ROOT / name) for name in names})
    temporary = saved_path.with_suffix('.tmp')
    temporary.write_text(json.dumps(saved, indent=2) + '\n')
    temporary.replace(saved_path)


def run(command, *, cwd=ROOT):
    with (ROOT / 'toolchains/setup.log').open('a') as log:
        log.write('\n' + repr([str(arg) for arg in command]) + '\n')
        log.flush()
        result = subprocess.run(command, cwd=cwd, stdout=log, stderr=subprocess.STDOUT)
    if result.returncode:
        raise RuntimeError(f'Setup command failed. See {ROOT / "toolchains/setup.log"}')


def capture(command):
    return subprocess.check_output(command, cwd=ROOT, text=True).strip()


def verify_compiler_source(pins):
    source = ROOT / 'toolchains/agbcc'
    if capture(['git', '-C', source, 'rev-parse', 'HEAD']) != pins['compiler']['source_commit']:
        raise RuntimeError('Existing agbcc source differs from the pinned revision')
    if capture(['git', '-C', source, 'status', '--porcelain', '--untracked-files=no']):
        raise RuntimeError('Existing agbcc source has tracked changes; setup will not overwrite it')


def ensure_python():
    folder = ROOT / 'toolchains/analysis-venv'
    if not folder.exists():
        print('Creating the Python environment…', flush=True)
        venv.EnvBuilder(with_pip=True).create(folder)
    python = folder / 'bin/python'
    requirements = [ROOT / 'config/analysis-requirements.txt', ROOT / 'config/progress-requirements.txt']
    expected = dict(line.strip().split('==') for p in requirements for line in p.read_text().splitlines()
                    if line.strip() and not line.startswith('#'))
    check = ('import importlib.metadata as m; expected=' + repr(expected) +
             '; assert all(m.version(k)==v for k,v in expected.items())')
    if subprocess.run([python, '-c', check], stdout=subprocess.DEVNULL,
                      stderr=subprocess.DEVNULL).returncode:
        print('Installing pinned analysis and treemap dependencies…', flush=True)
        run([python, '-m', 'pip', 'install', '--disable-pip-version-check',
             *[arg for p in requirements for arg in ('-r', p)]])
        run([python, '-c', check])


def ensure_compiler(pins):
    source = ROOT / 'toolchains/agbcc'
    if not source.exists():
        print('Downloading the pinned Thumb compiler source…', flush=True)
        run(['git', 'clone', '--no-checkout', pins['compiler']['source_url'], source])
        run(['git', '-C', source, 'checkout', '--detach', pins['compiler']['source_commit']])
    verify_compiler_source(pins)
    binary = source / 'gcc/agbcc'
    if binary.is_file():
        return set()
    print('Building the Thumb compiler…', flush=True)
    run(['make', '-C', source / 'gcc', '-j1'])
    verify_compiler_source(pins)
    return {'toolchains/agbcc/gcc/agbcc'}


def verify_archive(archive, expected):
    if sha(archive) != expected:
        raise RuntimeError(f'Binutils archive checksum mismatch: {archive}')


def ensure_binutils(pins):
    names = {name for name in pins['native_tool_sha256'] if '/binutils/' in name}
    if all((ROOT / name).is_file() for name in names):
        return set()
    spec = pins['binutils']
    archive = ROOT / 'toolchains' / spec['source_url'].rsplit('/', 1)[1]
    if not archive.exists():
        print('Downloading the pinned binutils archive…', flush=True)
        partial = archive.with_suffix(archive.suffix + '.partial')
        run(['curl', '--fail', '--location', '--retry', '2', '--output', partial, spec['source_url']])
        verify_archive(partial, spec['source_sha256'])
        partial.replace(archive)
    verify_archive(archive, spec['source_sha256'])
    print('Building the assembler and linker (this can take a few minutes)…', flush=True)
    # Extract the verified archive afresh; never trust an existing unpacked source tree.
    with tempfile.TemporaryDirectory(prefix='setup-binutils-', dir=ROOT / 'toolchains') as scratch:
        scratch = Path(scratch)
        run(['tar', '-xf', archive, '-C', scratch])
        source = scratch / archive.name.removesuffix('.tar.xz')
        build = scratch / 'build'
        build.mkdir()
        run([source / 'configure', '--prefix=' + str(ROOT / 'toolchains/binutils'),
             *spec['configure_options']], cwd=build)
        run(['make', '-j' + str(min(os.cpu_count() or 1, 6)), 'MAKEINFO=true',
             'all-binutils', 'all-gas', 'all-ld'], cwd=build)
        run(['make', 'MAKEINFO=true', 'install-binutils', 'install-gas', 'install-ld'], cwd=build)
    return names


def main():
    if sys.platform != 'darwin':
        raise RuntimeError('Automated setup currently supports macOS')
    if sys.version_info < (3, 10):
        raise RuntimeError('Python 3.10 or later is required')
    for name in ('git', 'make', 'curl', 'tar', 'xcrun'):
        if not shutil.which(name):
            raise RuntimeError(f'Missing {name}; install the Xcode command line tools first')
    host_clang = capture(['xcrun', 'clang', '--version'])
    (ROOT / 'toolchains').mkdir(exist_ok=True)
    pins = json.loads((ROOT / PIN).read_text())
    existing, profile_path = load_profile(ROOT)
    if profile_path:
        # Rerunning setup must not silently bless altered binaries or a changed compiler.
        verify_native(ROOT, existing, host_clang)
    else:
        existing = pending_profile(ROOT, pins, host_clang)
        for name, expected in existing['native_tool_sha256'].items():
            if (ROOT / name).exists() and sha(ROOT / name) != expected:
                raise RuntimeError(f'Unrecognised existing tool: {name}; setup will not adopt it')
    ensure_python()
    built = ensure_compiler(pins)
    record_completed(built, pins, host_clang)
    binutils = ensure_binutils(pins)
    record_completed(binutils, pins, host_clang)
    built |= binutils
    for name, expected in pins['native_tool_sha256'].items():
        if name not in built and sha(ROOT / name) != existing['native_tool_sha256'][name]:
            raise RuntimeError(f'Existing native tool changed during setup: {name}')
    for name, expected in (('arm-none-eabi-as', pins['binutils']['assembler_version']),
                           ('arm-none-eabi-ld', pins['binutils']['linker_version'])):
        if capture([ROOT / 'toolchains/binutils/bin' / name, '--version']).splitlines()[0] != expected:
            raise RuntimeError(f'{name} has an unexpected version')
    if not profile_path:
        profile = {'source_pin_sha256': sha(ROOT / PIN),
                   'native_tool_sha256': {name: sha(ROOT / name) for name in pins['native_tool_sha256']},
                   'host_clang': host_clang,
                   'scope': 'Provisioned tools only. Matching requires a successful make build.'}
        temporary = (ROOT / PROFILE).with_suffix('.tmp')
        temporary.write_text(json.dumps(profile, indent=2) + '\n')
        temporary.replace(ROOT / PROFILE)
    (ROOT / PENDING).unlink(missing_ok=True)
    print('Setup complete. Put your USA/Europe ROM in baseroms/, then run make build.')
    print('Native tool fingerprints are local; exact matching is checked on every build.')
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (OSError, RuntimeError, subprocess.CalledProcessError) as error:
        print(f'Setup failed: {error}', file=sys.stderr)
        sys.exit(1)
