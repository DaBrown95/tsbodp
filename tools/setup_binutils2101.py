#!/usr/bin/env python3
"""Provision the separate historical GNU assembler from pinned public source."""
import json
from pathlib import Path
import subprocess
import sys
import tempfile

from project import ROOT
from setup import capture, run, verify_archive
from setup_gcc302 import extract_source, verify_patch
from toolchain import (BINUTILS2101_PIN, BINUTILS2101_PROFILE, load_profile, sha,
                       source_tree_sha256, verify_binutils2101_source, verify_native)


def provision(root, pins, host, runner):
    spec = pins['assembler']
    binary = root / 'toolchains/binutils2101-build/gas/as-new'
    build = root / spec['build_directory']
    if binary.parent.parent != build:
        raise RuntimeError('Binutils2101 build directory differs from selected assembler')
    profile_path = root / BINUTILS2101_PROFILE
    if profile_path.exists() or binary.exists():
        lock, _ = load_profile(root, BINUTILS2101_PIN, BINUTILS2101_PROFILE)
        verify_native(root, lock, host)
        verify_binutils2101_source(root, lock)
        return False
    if build.exists() and (not build.is_dir() or any(build.iterdir())):
        raise RuntimeError('Incomplete Binutils2101 build requires inspection; it will not be adopted')
    archive = root / 'toolchains' / spec['source_url'].rsplit('/', 1)[1]
    verify_archive(archive, spec['source_sha256'])
    patch = verify_patch(root, spec, 'Binutils2101')
    source = root / spec['source_directory']
    if source.exists():
        if not source.is_dir() or source_tree_sha256(source) != spec['source_tree_sha256']:
            raise RuntimeError('Existing Binutils2101 source is not the pinned patched tree')
    else:
        with tempfile.TemporaryDirectory(prefix='binutils2101-source-', dir=root / 'toolchains') as scratch:
            prepared = extract_source(archive, Path(scratch), spec['source_version'], 'binutils')
            runner(['patch', '--batch', '--fuzz=0', '-p1', '-i', patch], cwd=prepared)
            if source_tree_sha256(prepared) != spec['source_tree_sha256']:
                raise RuntimeError('Binutils2101 patched source differs from its public pin')
            prepared.rename(source)
    build.mkdir(parents=True, exist_ok=True)
    runner(['env', *spec['configure_environment'], source / 'configure',
            '--prefix=' + str(root / spec['install_directory']),
            *spec['configure_options']], cwd=build)
    runner(['make', *spec['build_options']], cwd=build)
    verify_binutils2101_source(root, pins)
    if not binary.is_file():
        raise RuntimeError('Binutils2101 build did not produce the selected assembler')
    profile = {'source_pin_sha256': sha(root / BINUTILS2101_PIN),
               'native_tool_sha256': {name: sha(root / name) for name in pins['native_tool_sha256']},
               'host_clang': host,
               'scope': 'Fresh public archive plus pinned host declaration patch; matching requires make build.'}
    temporary = profile_path.with_suffix('.tmp')
    temporary.write_text(json.dumps(profile, indent=2) + '\n')
    temporary.replace(profile_path)
    verify_native(root, profile, host)
    return True


def main():
    if sys.platform != 'darwin':
        raise RuntimeError('Binutils2101 setup currently supports macOS')
    pins = json.loads((ROOT / BINUTILS2101_PIN).read_text())
    host = capture(['xcrun', 'clang', '--version'])
    (ROOT / 'toolchains').mkdir(exist_ok=True)
    spec = pins['assembler']
    archive = ROOT / 'toolchains' / spec['source_url'].rsplit('/', 1)[1]
    if not archive.exists():
        partial = archive.with_suffix(archive.suffix + '.partial')
        run(['curl', '--fail', '--location', '--retry', '2', '--output', partial, spec['source_url']])
        verify_archive(partial, spec['source_sha256'])
        partial.replace(archive)
    built = provision(ROOT, pins, host, run)
    print('Binutils2101 assembler ' + ('freshly built and enrolled.' if built else 'verified.'))
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (OSError, ValueError, RuntimeError, subprocess.CalledProcessError) as error:
        print(f'Binutils2101 setup failed: {error}', file=sys.stderr)
        sys.exit(1)
