"""Public source pins and immutable, machine-local native tool fingerprints."""
import hashlib
import json
import re
import stat
import subprocess
from pathlib import Path, PurePosixPath

PROFILE = Path('toolchains/host-profile.json')
PIN = Path('config/pilot-toolchain.json')
ARM_PIN = Path('config/arm-toolchain.json')
ARM_PROFILE = Path('toolchains/arm-host-profile.json')
OLD_PIN = Path('config/agbcc-old-toolchain.json')
OLD_PROFILE = Path('toolchains/agbcc-old-host-profile.json')
OLD_BUILD = Path('toolchains/agbcc-old-build')
GCC302_PIN = Path('config/gcc302-toolchain.json')
GCC302_PROFILE = Path('toolchains/gcc302-host-profile.json')
GCC302_HWI32_PIN = Path('config/gcc302-hwi32-toolchain.json')
GCC302_HWI32_PROFILE = Path('toolchains/gcc302-hwi32-host-profile.json')
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
        'agbcc_old': ('toolchains/agbcc-old-build/old_agbcc', OLD_PIN, OLD_PROFILE, ('Thumb',)),
        'gcc302': ('toolchains/gcc302-build/gcc/cc1', GCC302_PIN, GCC302_PROFILE, ('Thumb', 'ARM')),
        'gcc302_hwi32': ('toolchains/gcc302-hwi32-build/gcc/cc1', GCC302_HWI32_PIN,
                        GCC302_HWI32_PROFILE, ('Thumb', 'ARM')),
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
    if compiler_id in ('gcc302', 'gcc302_hwi32') and mode == 'Thumb' and '-mthumb' not in selected_flags:
        raise ValueError('GCC302 Thumb selection requires explicit -mthumb')
    if compiler_id in ('gcc302', 'gcc302_hwi32') and mode == 'ARM' and '-marm' not in selected_flags:
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


def _regular_source(path, root):
    """Do not follow substituted source directories or symbolic links."""
    for item in (path, *path.parents):
        if item == root:
            break
        if item.is_symlink():
            raise RuntimeError('Old agbcc source contains an unexpected symbolic link')
    if not stat.S_ISREG(path.lstat().st_mode):
        raise RuntimeError('Old agbcc source input is not a regular file')


def agbcc_old_source_files(root, pins):
    """Verify the pinned Git blobs, paths and modes, excluding generated files."""
    spec = pins['compiler']
    if (spec['source_subdirectory'] != 'gcc' or
            spec['build_directory'] != OLD_BUILD.as_posix()):
        raise RuntimeError('Old agbcc source or build directory differs from its isolated recipe')
    # The upstream Makefile does not order every RTL object after genrtl.h.
    # A truly source-only bootstrap must follow upstream build.sh's serial job.
    if spec['build_options'] != ['old', '-j1']:
        raise RuntimeError('Old agbcc source-only bootstrap requires the pinned serial recipe')
    repository = root / 'toolchains/agbcc'
    if repository.is_symlink():
        raise RuntimeError('Old agbcc source repository must not be a symbolic link')

    def git(*args):
        try:
            return subprocess.check_output(['git', '-C', repository, *args])
        except subprocess.CalledProcessError as error:
            raise RuntimeError('Unable to verify old agbcc pinned Git source') from error

    if git('rev-parse', 'HEAD').decode().strip() != spec['source_commit']:
        raise RuntimeError('Old agbcc source differs from the pinned revision')
    if git('status', '--porcelain', '--untracked-files=no').strip():
        raise RuntimeError('Old agbcc source has tracked changes')
    rows = git('ls-tree', '-rz', '--full-tree', spec['source_commit'], 'gcc/')
    records = []
    seen = set()
    for row in rows.split(b'\0'):
        if not row:
            continue
        information, name = row.split(b'\t', 1)
        mode, kind, object_id = information.split()
        path = PurePosixPath(name.decode('utf-8'))
        if (mode not in (b'100644', b'100755') or kind != b'blob' or
                not re.fullmatch(b'[0-9a-f]{40}', object_id) or
                path.is_absolute() or '..' in path.parts or
                len(path.parts) < 2 or path.parts[0] != 'gcc'):
            raise RuntimeError('Unexpected old agbcc tracked source entry')
        relative = Path(*path.parts[1:])
        if relative in seen:
            raise RuntimeError('Duplicate old agbcc tracked source entry')
        seen.add(relative)
        source = repository / Path(*path.parts)
        _regular_source(source, root)
        data = source.read_bytes()
        blob = hashlib.sha1(b'blob ' + str(len(data)).encode() + b'\0' + data).hexdigest()
        if blob != object_id.decode():
            raise RuntimeError('Old agbcc live source differs from its pinned Git blob')
        permissions = int(mode, 8) & 0o777
        if stat.S_IMODE(source.stat().st_mode) != permissions:
            raise RuntimeError('Old agbcc source mode differs from its pinned Git mode')
        records.append((relative, permissions, source, hashlib.sha256(data).hexdigest()))
    digest = hashlib.sha256()
    for relative, permissions, source, fingerprint in sorted(records):
        digest.update(relative.as_posix().encode() + b'\0' +
                      ('100%03o' % permissions).encode() + b'\0' + bytes.fromhex(fingerprint))
    if (len(records) != spec['tracked_source_file_count'] or
            digest.hexdigest() != spec['tracked_source_tree_sha256']):
        raise RuntimeError('Old agbcc tracked source identity differs from its public pin')
    return records


def verify_agbcc_old_source(root, pins):
    """Verify the ordinary isolated copies as well as their original Git inputs."""
    records = agbcc_old_source_files(root, pins)
    original_inodes = {(p.stat().st_dev, p.stat().st_ino) for _, _, p, _ in records}
    inputs = []
    for relative, permissions, source, fingerprint in records:
        copied = root / OLD_BUILD / relative
        _regular_source(copied, root)
        identity = copied.stat()
        if ((identity.st_dev, identity.st_ino) in original_inodes or
                stat.S_IMODE(identity.st_mode) != permissions or sha(copied) != fingerprint):
            raise RuntimeError('Old agbcc isolated source copy changed or aliases the live source')
        inputs.extend((source, copied))
    return inputs


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
