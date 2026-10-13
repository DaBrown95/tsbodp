#!/usr/bin/env python3
"""Provision GCC3.0.2 with 32-bit compiler integers on the native LP64 host."""
import json
import subprocess
import sys

from project import ROOT
from setup import capture, run
from setup_gcc302 import provision
from toolchain import GCC302_HWI32_PIN, GCC302_HWI32_PROFILE


def main():
    if sys.platform != 'darwin':
        raise RuntimeError('GCC302 setup currently supports macOS')
    pins = json.loads((ROOT / GCC302_HWI32_PIN).read_text())
    host = capture(['xcrun', 'clang', '--version'])
    # Reuse the locally verified public archive. The ordinary GCC302 setup
    # supplies it; no alternative source or unknown existing build is adopted.
    built = provision(ROOT, pins, host, run, GCC302_HWI32_PIN, GCC302_HWI32_PROFILE)
    print('GCC302 HWI32 backend ' + ('freshly built and enrolled.' if built else 'verified.'))
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (OSError, ValueError, RuntimeError, subprocess.CalledProcessError) as error:
        print(f'GCC302 HWI32 setup failed: {error}', file=sys.stderr)
        sys.exit(1)
