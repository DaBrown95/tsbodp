"""Public source pins and immutable, machine-local native tool fingerprints."""
import hashlib
import json
import re
from pathlib import Path

PROFILE = Path('toolchains/host-profile.json')
PIN = Path('config/pilot-toolchain.json')
ARM_PIN = Path('config/arm-toolchain.json')
ARM_PROFILE = Path('toolchains/arm-host-profile.json')
GCC302_PIN = Path('config/gcc302-toolchain.json')
GCC302_PROFILE = Path('toolchains/gcc302-host-profile.json')
BINUTILS2101_PIN = Path('config/binutils2101-toolchain.json')
BINUTILS2101_PROFILE = Path('toolchains/binutils2101-host-profile.json')


def modern_assembler_abi_flags():
    """Use GNU object ABI and software FP consistently, including data objects."""
    # GNU2.10.1 -mno-fpu uses the original FPA word convention. softvfp
    # additionally advertises pure-endian VFP doubles and conflicts at link.
    return ['-meabi=gnu', '-mfpu=softfpa']


def assembler_selection(function):
    """Select an assembler profile without rewriting compiler assembly."""
    assembler_id = function.get('assembler_id', 'binutils')
    mode = function.get('mode', 'Thumb')
    if mode not in ('ARM', 'Thumb'):
        raise ValueError('Unsupported assembler instruction mode')
    if assembler_id == 'binutils':
        return {'assembler_id': assembler_id,
                'executable': Path('toolchains/binutils/bin/arm-none-eabi-as'),
                'pin': PIN, 'profile': PROFILE,
                'source_flags': ['-mcpu=arm7tdmi', *([] if mode == 'ARM' else ['-mthumb']),
                                 '--no-pad-sections', *modern_assembler_abi_flags()],
                'extern_flags': modern_assembler_abi_flags()}
    if assembler_id == 'binutils2101':
        # Set the software-FP convention after selecting the CPU. Both input
        # objects need the same convention for the unchanged modern linker.
        flags = ['-marm7tdmi', '-mno-fpu', *([] if mode == 'ARM' else ['-mthumb'])]
        return {'assembler_id': assembler_id,
                'executable': Path('toolchains/binutils2101-build/gas/as-new'),
                'pin': BINUTILS2101_PIN, 'profile': BINUTILS2101_PROFILE,
                'source_flags': flags, 'extern_flags': list(flags)}
    raise ValueError('Unknown assembler_id')


def compiler_selection(function, flags):
    """Resolve only named, pinned backends; a manifest cannot select a tool path."""
    mode = function.get('mode', 'Thumb')
    compiler_id = function.get('compiler_id', 'agbcc_arm' if mode == 'ARM' else 'agbcc')
    compilers = {
        'agbcc': ('toolchains/agbcc/gcc/agbcc', PIN, PROFILE, ('Thumb',)),
        'agbcc_arm': ('toolchains/agbcc-arm-build/cc1', ARM_PIN, ARM_PROFILE, ('ARM',)),
        'gcc302': ('toolchains/gcc302-build/gcc/cc1', GCC302_PIN, GCC302_PROFILE, ('Thumb', 'ARM')),
    }
    if not isinstance(compiler_id, str) or compiler_id not in compilers:
        raise ValueError('Unknown compiler_id')
    binary, pin, local, modes = compilers[compiler_id]
    if mode not in modes:
        raise ValueError('Compiler does not support the selected execution mode')
    selected_flags = function.get('compiler_flags', flags)
    if (not isinstance(selected_flags, list) or
            any(not isinstance(flag, str) or not flag for flag in selected_flags)):
        raise ValueError('Compiler flags must be a list of nonempty strings')
    if mode == 'ARM' and '-mthumb' in selected_flags:
        raise ValueError('ARM backend cannot compile Thumb instructions')
    if compiler_id == 'gcc302' and mode == 'Thumb' and '-mthumb' not in selected_flags:
        raise ValueError('GCC302 Thumb selection requires explicit -mthumb')
    if compiler_id == 'gcc302' and mode == 'ARM' and '-marm' not in selected_flags:
        raise ValueError('GCC302 ARM selection requires explicit -marm')
    if mode == 'Thumb' and '-marm' in selected_flags:
        raise ValueError('Thumb selection cannot request ARM instructions')
    return {'compiler_id': compiler_id, 'executable': Path(binary), 'pin': pin,
            'profile': local, 'flags': list(selected_flags)}


def source_tree_sha256(folder):
    """Fingerprint relative names and contents, without including host paths."""
    digest = hashlib.sha256()
    for path in sorted(folder.rglob('*')):
        if path.is_symlink():
            raise RuntimeError('Compiler source contains an unexpected symbolic link')
        if path.is_file():
            digest.update(path.relative_to(folder).as_posix().encode() + b'\0')
            digest.update(bytes.fromhex(sha(path)))
    return digest.hexdigest()


def optimization_flags(flags, optimization):
    """Vary optimization without discarding instruction mode or CPU options."""
    if optimization not in ('-O0', '-O1', '-O2', '-O3', '-Os'):
        raise ValueError('Unsupported optimization trial')
    return [optimization, *[flag for flag in flags if not re.fullmatch(r'-O(?:[0-9]+|s|g|fast)?', flag)]]


def verify_archive_source(root, spec, label):
    archive = root / 'toolchains' / spec['source_url'].rsplit('/', 1)[1]
    patch = root / spec['compatibility_patch']
    for path, expected in ((archive, spec['source_sha256']),
                           (patch, spec['compatibility_patch_sha256'])):
        if not path.is_file() or sha(path) != expected:
            raise RuntimeError(label + ' source archive or compatibility patch changed')
    source = root / spec['source_directory']
    if not source.is_dir() or source_tree_sha256(source) != spec['source_tree_sha256']:
        raise RuntimeError(label + ' patched source changed or is missing')


def verify_gcc302_source(root, pins):
    verify_archive_source(root, pins['compiler'], 'GCC302')


def verify_binutils2101_source(root, pins):
    verify_archive_source(root, pins['assembler'], 'Binutils2101')


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


def load_profile(root, pin=PIN, local=PROFILE):
    pins = json.loads((root / pin).read_text())
    profile_path = root / local
    if not profile_path.exists():
        return pins, None
    profile = json.loads(profile_path.read_text())
    validate_profile(profile, pins, sha(root / pin))
    return {**pins, 'native_tool_sha256': profile['native_tool_sha256'],
            'host_clang': profile['host_clang']}, local


def verify_native(root, profile, host_clang):
    for name, expected in profile['native_tool_sha256'].items():
        if not (root / name).is_file() or sha(root / name) != expected:
            raise RuntimeError(f'Native tool changed or is missing: {name}')
    if host_clang != profile['host_clang']:
        raise RuntimeError('Host preprocessor changed from the recorded tool profile')
