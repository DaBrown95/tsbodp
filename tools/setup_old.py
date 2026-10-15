#!/usr/bin/env python3
"""Build the upstream old Thumb backend in a separate verified source copy."""
import json
import os
import stat
import subprocess
import sys

from project import ROOT
from setup import capture, run
from toolchain import (OLD_BUILD, OLD_PIN, OLD_PROFILE, agbcc_old_source_files,
                       load_profile, sha, verify_agbcc_old_source, verify_native)


def provision(root, pins, host, runner):
    """Verify existing tools; only a fresh isolated build may enroll a profile."""
    binary = root / OLD_BUILD / 'old_agbcc'
    if set(pins['native_tool_sha256']) != {binary.relative_to(root).as_posix()}:
        raise RuntimeError('Old agbcc native pin differs from its isolated build directory')
    records = agbcc_old_source_files(root, pins)
    profile_path = root / OLD_PROFILE
    if profile_path.is_symlink():
        raise RuntimeError('Old agbcc profile must not be a symbolic link')
    if profile_path.exists() or binary.exists() or binary.is_symlink():
        if binary.is_symlink() or not binary.is_file() or not stat.S_ISREG(binary.stat().st_mode):
            raise RuntimeError('Old agbcc native tool must be a regular file')
        lock, _ = load_profile(root, OLD_PIN, OLD_PROFILE)
        verify_agbcc_old_source(root, lock)
        verify_native(root, lock, host)
        return False
    build = root / OLD_BUILD
    if build.is_symlink() or (build.exists() and
            (not build.is_dir() or any(build.iterdir()))):
        raise RuntimeError('Incomplete old agbcc build needs inspection; it will not be adopted')
    # Keep each copied input independent from the live checkout and preserve the
    # Git mode. Existing generated outputs are never copied into a fresh build.
    build.mkdir(parents=True, exist_ok=True)
    for relative, permissions, source, _ in records:
        destination = build / relative
        destination.parent.mkdir(parents=True, exist_ok=True)
        with destination.open('xb') as output:
            output.write(source.read_bytes())
        destination.chmod(permissions)
    verify_agbcc_old_source(root, pins)
    runner(['make', *pins['compiler']['build_options']], cwd=build)
    verify_agbcc_old_source(root, pins)
    if binary.is_symlink() or not binary.is_file():
        raise RuntimeError('Old agbcc build did not produce the selected regular compiler')
    profile = {'source_pin_sha256': sha(root / OLD_PIN),
               'native_tool_sha256': {name: sha(root / name) for name in pins['native_tool_sha256']},
               'host_clang': host,
               'scope': 'Fresh isolated upstream old backend; exact matching requires make build.'}
    # Refuse concurrent enrollment or an interrupted profile write rather than
    # replacing a pre-existing lock with freshly observed native bytes.
    temporary = profile_path.with_suffix('.tmp')
    with temporary.open('x') as output:
        output.write(json.dumps(profile, indent=2) + '\n')
        output.flush()
        os.fsync(output.fileno())
    os.link(temporary, profile_path)
    temporary.unlink()
    verify_native(root, profile, host)
    return True


def main():
    if sys.platform != 'darwin':
        raise RuntimeError('Old agbcc setup currently supports macOS')
    pins = json.loads((ROOT / OLD_PIN).read_text())
    host = capture(['xcrun', 'clang', '--version'])
    current, _ = load_profile(ROOT)
    verify_native(ROOT, current, host)
    if pins['compiler']['source_commit'] != current['compiler']['source_commit']:
        raise RuntimeError('Old and current agbcc backends must use the same pinned source revision')
    built = provision(ROOT, pins, host, run)
    print('Old agbcc backend ' + ('freshly built and enrolled.' if built else 'verified.'))
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (OSError, ValueError, RuntimeError, subprocess.CalledProcessError) as error:
        print(f'Old agbcc setup failed: {error}', file=sys.stderr)
        sys.exit(1)
