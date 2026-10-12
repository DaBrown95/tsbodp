#!/usr/bin/env python3
"""Build the separately pinned ARM backend without changing the Thumb profile."""
import json
from pathlib import Path
import subprocess
import sys

from project import ROOT
from setup import capture, run, verify_compiler_source
from toolchain import ARM_PIN, ARM_PROFILE, load_profile, sha, verify_native


def main():
    pins = json.loads((ROOT / ARM_PIN).read_text())
    host = capture(['xcrun', 'clang', '--version'])
    thumb, _ = load_profile(ROOT)
    verify_native(ROOT, thumb, host)
    if pins['compiler']['source_commit'] != thumb['compiler']['source_commit']:
        raise RuntimeError('ARM and Thumb backends must use the same pinned source revision')
    verify_compiler_source(pins)
    lock, local = load_profile(ROOT, ARM_PIN, ARM_PROFILE)
    binary = ROOT / next(iter(pins['native_tool_sha256']))
    if local or binary.exists():
        # Existing tools are verified, never silently enrolled or overwritten.
        verify_native(ROOT, lock, host)
        print('Pinned ARM backend verified.')
        return 0
    build = binary.parent
    if build.exists() and any(build.iterdir()):
        raise RuntimeError('Incomplete ARM build directory needs inspection before rebuilding')
    build.mkdir(parents=True, exist_ok=True)
    source = ROOT / 'toolchains/agbcc' / pins['compiler']['source_subdirectory']
    run([source / 'configure', *pins['compiler']['configure_options']], cwd=build)
    # The pinned source has a generated parser; the out-of-tree makefile expects
    # its local filename rather than resolving it through the source directory.
    (build / 'c-parse.c').symlink_to(Path('../agbcc/gcc_arm/c-parse.c'))
    run(['make', *pins['compiler']['build_options']], cwd=build)
    verify_compiler_source(pins)
    profile = {'source_pin_sha256': sha(ROOT / ARM_PIN),
               'native_tool_sha256': {name: sha(ROOT / name) for name in pins['native_tool_sha256']},
               'host_clang': host,
               'scope': 'Freshly built ARM backend only; exact matching requires make build.'}
    temporary = (ROOT / ARM_PROFILE).with_suffix('.tmp')
    temporary.write_text(json.dumps(profile, indent=2) + '\n')
    temporary.replace(ROOT / ARM_PROFILE)
    verify_native(ROOT, profile, host)
    print('ARM backend built; machine-local fingerprints recorded separately.')
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (OSError, RuntimeError, subprocess.CalledProcessError) as error:
        print(f'ARM setup failed: {error}', file=sys.stderr)
        sys.exit(1)
