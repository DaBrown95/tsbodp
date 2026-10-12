"""Public source pins and immutable, machine-local native tool fingerprints."""
import hashlib
import json
from pathlib import Path

PROFILE = Path('toolchains/host-profile.json')
PIN = Path('config/pilot-toolchain.json')


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def validate_profile(profile, pins, pin_digest):
    if profile.get('source_pin_sha256') != pin_digest:
        raise RuntimeError('Setup profile is stale: public toolchain pins changed')
    fingerprints = profile.get('native_tool_sha256', {})
    if not isinstance(fingerprints, dict) or set(fingerprints) != set(pins['native_tool_sha256']):
        raise RuntimeError('Setup profile does not cover every required native tool')
    if any(not isinstance(value, str) or len(value) != 64 or
           any(c not in '0123456789abcdef' for c in value) for value in fingerprints.values()):
        raise RuntimeError('Setup profile contains an invalid tool fingerprint')
    if not isinstance(profile.get('host_clang'), str) or not profile['host_clang'].strip():
        raise RuntimeError('Setup profile is missing the host preprocessor version')


def load_profile(root):
    pins = json.loads((root / PIN).read_text())
    profile_path = root / PROFILE
    if not profile_path.exists():
        return pins, None
    profile = json.loads(profile_path.read_text())
    validate_profile(profile, pins, sha(root / PIN))
    return {**pins, 'native_tool_sha256': profile['native_tool_sha256'],
            'host_clang': profile['host_clang']}, PROFILE


def verify_native(root, profile, host_clang):
    for name, expected in profile['native_tool_sha256'].items():
        if not (root / name).is_file() or sha(root / name) != expected:
            raise RuntimeError(f'Native tool changed or is missing: {name}')
    if host_clang != profile['host_clang']:
        raise RuntimeError('Host preprocessor changed from the recorded tool profile')
