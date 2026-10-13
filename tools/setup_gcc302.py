#!/usr/bin/env python3
"""Provision the separate public GCC3.0.2 backend from verified source."""
import json
from pathlib import Path, PurePosixPath
import subprocess
import sys
import tarfile
import tempfile

from project import ROOT
from setup import capture, run, verify_archive
from toolchain import (GCC302_PIN, GCC302_PROFILE, load_profile, sha,
                       source_tree_sha256, verify_gcc302_source, verify_native)


def verify_patch(root, spec, label='GCC302'):
    patch = root / spec['compatibility_patch']
    if not patch.is_file() or sha(patch) != spec['compatibility_patch_sha256']:
        raise RuntimeError(label + ' compatibility patch checksum mismatch')
    return patch


def extract_source(archive, destination, version, package='gcc'):
    """Reject unexpected archive entries before extracting anything."""
    if package not in ('gcc', 'binutils'):
        raise ValueError('Unsupported source package')
    prefix = package + '-' + version
    with tarfile.open(archive) as stream:
        members = stream.getmembers()
        for member in members:
            path = PurePosixPath(member.name)
            if (path.is_absolute() or '..' in path.parts or not path.parts or
                    path.parts[0] != prefix or not (member.isfile() or member.isdir())):
                raise RuntimeError('Unexpected source archive entry')
        options = {'filter': 'data'} if hasattr(tarfile, 'data_filter') else {}
        stream.extractall(destination, members=members, **options)
    return destination / prefix


def prepare_source(root, pins, runner):
    spec = pins['compiler']
    source = root / spec['source_directory']
    archive = root / 'toolchains' / spec['source_url'].rsplit('/', 1)[1]
    verify_archive(archive, spec['source_sha256'])
    patch = verify_patch(root, spec)
    if source.exists():
        if not source.is_dir() or source_tree_sha256(source) != spec['source_tree_sha256']:
            raise RuntimeError('Existing GCC302 source is not the pinned patched tree')
        return source
    with tempfile.TemporaryDirectory(prefix='gcc302-source-', dir=root / 'toolchains') as scratch:
        prepared = extract_source(archive, Path(scratch), spec['source_version'])
        runner(['patch', '--batch', '--fuzz=0', '-p1', '-i', patch], cwd=prepared)
        if source_tree_sha256(prepared) != spec['source_tree_sha256']:
            raise RuntimeError('GCC302 patched source does not match its public pin')
        prepared.rename(source)
    return source


def provision(root, pins, host, runner, pin=GCC302_PIN, local=GCC302_PROFILE):
    """Only a fresh build may enroll new native fingerprints."""
    build = root / pins['compiler']['build_directory']
    binary = build / 'gcc/cc1'
    if set(pins['native_tool_sha256']) != {binary.relative_to(root).as_posix()}:
        raise RuntimeError('GCC302 native pin differs from the selected build directory')
    profile_path = root / local
    if profile_path.exists() or binary.exists():
        lock, _ = load_profile(root, pin, local)
        verify_native(root, lock, host)
        verify_gcc302_source(root, lock)
        return False
    if build.exists() and (not build.is_dir() or any(build.iterdir())):
        raise RuntimeError('Incomplete GCC302 build requires inspection; it will not be adopted')
    source = prepare_source(root, pins, runner)
    build.mkdir(parents=True, exist_ok=True)
    spec = pins['compiler']
    runner(['env', *spec['configure_environment'], source / 'configure',
            '--prefix=' + str(root / spec['install_directory']),
            *spec['configure_options']], cwd=build)
    for step in spec['build_steps']:
        runner(['make', *step['options']], cwd=build / step['directory'])
    verify_gcc302_source(root, pins)
    if not binary.is_file():
        raise RuntimeError('GCC302 build did not produce the selected compiler')
    profile = {'source_pin_sha256': sha(root / pin),
               'native_tool_sha256': {name: sha(root / name) for name in pins['native_tool_sha256']},
               'host_clang': host,
               'scope': 'Fresh public archive plus pinned host patch; exact matching requires make build.'}
    temporary = profile_path.with_suffix('.tmp')
    temporary.write_text(json.dumps(profile, indent=2) + '\n')
    temporary.replace(profile_path)
    verify_native(root, profile, host)
    return True


def main():
    if sys.platform != 'darwin':
        raise RuntimeError('GCC302 setup currently supports macOS')
    pins = json.loads((ROOT / GCC302_PIN).read_text())
    host = capture(['xcrun', 'clang', '--version'])
    (ROOT / 'toolchains').mkdir(exist_ok=True)
    spec = pins['compiler']
    archive = ROOT / 'toolchains' / spec['source_url'].rsplit('/', 1)[1]
    if not archive.exists():
        partial = archive.with_suffix(archive.suffix + '.partial')
        run(['curl', '--fail', '--location', '--retry', '2', '--output', partial, spec['source_url']])
        verify_archive(partial, spec['source_sha256'])
        partial.replace(archive)
    built = provision(ROOT, pins, host, run)
    print('GCC302 backend ' + ('freshly built and enrolled.' if built else 'verified.'))
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (OSError, ValueError, RuntimeError, subprocess.CalledProcessError) as error:
        print(f'GCC302 setup failed: {error}', file=sys.stderr)
        sys.exit(1)
