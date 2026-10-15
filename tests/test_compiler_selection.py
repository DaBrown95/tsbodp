"""Selected compilers are pinned independently and unknown tools are rejected."""
import copy
import hashlib
import io
import json
from pathlib import Path
import sys
import tarfile
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from toolchain import (PIN, PROFILE, GCC302_PIN, GCC302_PROFILE, compiler_selection,
                       load_profile, sha, source_tree_sha256, verify_gcc302_source,
                       verify_native, optimization_flags)
from setup_gcc302 import extract_source, prepare_source, provision


class SelectionTests(unittest.TestCase):
    def test_default_compilers_and_flags_remain_unchanged(self):
        flags = ['-O2', '-mthumb-interwork']
        thumb = compiler_selection({}, flags)
        arm = compiler_selection({'mode': 'ARM'}, flags)
        self.assertEqual(thumb['executable'], Path('toolchains/agbcc/gcc/agbcc'))
        self.assertEqual(arm['executable'], Path('toolchains/agbcc-arm-build/cc1'))
        self.assertEqual(thumb['flags'], flags)
        self.assertEqual(arm['flags'], flags)

    def test_known_compiler_requires_explicit_execution_mode_flags(self):
        for mode, flag in [('Thumb', '-mthumb'), ('ARM', '-marm')]:
            with self.subTest(mode=mode):
                selection = compiler_selection({'compiler_id': 'gcc302', 'mode': mode,
                         'compiler_flags': ['-O3', flag, '-mthumb-interwork']}, ['-O2'])
                self.assertEqual(selection['executable'], Path('toolchains/gcc302-build/gcc/cc1'))
                self.assertEqual(selection['pin'], GCC302_PIN)
                self.assertEqual(selection['flags'][0], '-O3')
                with self.assertRaisesRegex(ValueError, 'explicit'):
                    compiler_selection({'compiler_id': 'gcc302', 'mode': mode}, ['-O3'])

    def test_old_thumb_backend_has_its_own_path_and_preserves_explicit_flags(self):
        selection = compiler_selection({'compiler_id': 'agbcc_old',
                                        'compiler_flags': ['-O2']}, ['-O2', '-mthumb-interwork'])
        self.assertEqual(selection['executable'], Path('toolchains/agbcc-old-build/old_agbcc'))
        self.assertEqual(selection['pin'], Path('config/agbcc-old-toolchain.json'))
        self.assertEqual(selection['profile'], Path('toolchains/agbcc-old-host-profile.json'))
        self.assertEqual(selection['flags'], ['-O2'])
        for mode, flags in [('ARM', ['-O2']), ('Thumb', ['-O2', '-marm'])]:
            with self.subTest(mode=mode), self.assertRaises(ValueError):
                compiler_selection({'compiler_id': 'agbcc_old', 'mode': mode}, flags)

    def test_unknown_paths_modes_and_contradictory_flags_reject(self):
        invalid = [({'compiler_id': '../../untrusted'}, ['-O2']),
                   ({'compiler_id': None}, ['-O2']),
                   ({'mode': 'ARM', 'compiler_id': 'agbcc'}, ['-O2']),
                   ({'mode': 'unknown'}, ['-O2']),
                   ({'mode': 'ARM', 'compiler_id': 'gcc302'}, ['-O3', '-mthumb', '-marm']),
                   ({'compiler_id': 'gcc302'}, ['-O3', '-mthumb', '-marm']),
                   ({'compiler_flags': '-O3'}, ['-O2']),
                   ({'compiler_flags': ['']}, ['-O2'])]
        for function, flags in invalid:
            with self.subTest(function=function), self.assertRaises(ValueError):
                compiler_selection(function, flags)

    def test_optimization_matrix_retains_mode_and_cpu_flags(self):
        flags = ['-O3', '-marm', '-mthumb-interwork', '-fomit-frame-pointer', '-mcpu=arm7tdmi']
        varied = optimization_flags(flags, '-O1')
        self.assertEqual(varied, ['-O1', *flags[1:]])
        compiler_selection({'compiler_id': 'gcc302', 'mode': 'ARM'}, varied)


class Gcc302ProvisionTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        (self.root / 'toolchains').mkdir()
        (self.root / 'config').mkdir()
        (self.root / 'tools').mkdir()
        self.patch = self.root / 'tools/compat.patch'
        self.patch.write_bytes(b'pinned patch')
        self.archive = self.root / 'toolchains/gcc-core-3.0.2.tar.gz'
        with tarfile.open(self.archive, 'w:gz') as stream:
            info = tarfile.TarInfo('gcc-3.0.2/main.c')
            info.size = 8
            stream.addfile(info, io.BytesIO(b'original'))
        # Derive the expected patched-tree fingerprint independently of setup.
        expected = self.root / 'expected'
        expected.mkdir()
        (expected / 'main.c').write_bytes(b'patched')
        self.name = 'toolchains/gcc302-build/gcc/cc1'
        self.pins = {'compiler': {'source_url': 'https://example.invalid/gcc-core-3.0.2.tar.gz',
                 'source_version': '3.0.2', 'source_sha256': sha(self.archive),
                 'compatibility_patch': 'tools/compat.patch',
                 'compatibility_patch_sha256': sha(self.patch),
                 'source_directory': 'toolchains/gcc302-source',
                 'source_tree_sha256': source_tree_sha256(expected),
                 'build_directory': 'toolchains/gcc302-build',
                 'install_directory': 'toolchains/gcc302-install',
                 'configure_environment': ['CC=clang', 'CFLAGS=-std=gnu89'],
                 'configure_options': ['--target=arm-elf'],
                 'build_steps': [{'directory': 'libiberty', 'options': ['all']},
                                 {'directory': 'gcc', 'options': ['cc1']}]},
                 'native_tool_sha256': {self.name: hashlib.sha256(b'original native').hexdigest()},
                 'host_clang': 'original host'}
        self.pin_path = self.root / GCC302_PIN
        self.pin_path.write_text(json.dumps(self.pins))
        self.commands = []

    def runner(self, command, *, cwd):
        self.commands.append([str(arg) for arg in command])
        if command[0] == 'patch':
            (cwd / 'main.c').write_bytes(b'patched')
        elif command[0] == 'make':
            binary = self.root / self.name
            binary.parent.mkdir(parents=True, exist_ok=True)
            binary.write_bytes(b'fresh native')

    def test_fresh_build_enrolls_native_fingerprint_without_changing_public_pin(self):
        before = self.pin_path.read_bytes()
        self.assertTrue(provision(self.root, self.pins, 'new host', self.runner))
        self.assertEqual(self.pin_path.read_bytes(), before)
        lock, local = load_profile(self.root, GCC302_PIN, GCC302_PROFILE)
        self.assertEqual(local, GCC302_PROFILE)
        self.assertEqual(lock['compiler'], self.pins['compiler'])
        verify_native(self.root, lock, 'new host')
        verify_gcc302_source(self.root, lock)
        self.assertFalse((self.root / PROFILE).exists())
        self.assertFalse(provision(self.root, self.pins, 'new host', self.runner))
        self.assertEqual(len(self.commands), 4)
        self.assertIn('CFLAGS=-std=gnu89', self.commands[1])
        self.assertTrue(any(arg.startswith('--prefix=') for arg in self.commands[1]))

    def test_existing_unknown_binary_cannot_be_adopted(self):
        binary = self.root / self.name
        binary.parent.mkdir(parents=True)
        binary.write_bytes(b'unknown native')
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            provision(self.root, self.pins, 'original host', self.runner)
        self.assertFalse((self.root / GCC302_PROFILE).exists())
        self.assertEqual(self.commands, [])

    def test_incomplete_build_cannot_be_adopted(self):
        build = self.root / 'toolchains/gcc302-build'
        build.mkdir()
        (build / 'old.o').write_bytes(b'unverified object')
        with self.assertRaisesRegex(RuntimeError, 'Incomplete'):
            provision(self.root, self.pins, 'new host', self.runner)
        self.assertEqual(self.commands, [])

    def test_missing_pin_missing_binary_and_changed_host_reject(self):
        self.pin_path.unlink()
        with self.assertRaises(FileNotFoundError):
            load_profile(self.root, GCC302_PIN, GCC302_PROFILE)
        self.pin_path.write_text(json.dumps(self.pins))
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            verify_native(self.root, self.pins, 'original host')
        provision(self.root, self.pins, 'new host', self.runner)
        with self.assertRaisesRegex(RuntimeError, 'preprocessor'):
            provision(self.root, self.pins, 'changed host', self.runner)
        (self.root / self.name).unlink()
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            provision(self.root, self.pins, 'new host', self.runner)

    def test_stale_pin_and_altered_native_patch_archive_or_source_reject(self):
        provision(self.root, self.pins, 'new host', self.runner)
        paths = [self.root / self.name, self.patch, self.archive,
                 self.root / 'toolchains/gcc302-source/main.c']
        for path in paths:
            original = path.read_bytes()
            path.write_bytes(original + b'changed')
            with self.subTest(path=path.name), self.assertRaises(RuntimeError):
                provision(self.root, self.pins, 'new host', self.runner)
            path.write_bytes(original)
        changed = copy.deepcopy(self.pins)
        changed['compiler']['source_version'] = 'different'
        self.pin_path.write_text(json.dumps(changed))
        with self.assertRaisesRegex(RuntimeError, 'stale'):
            provision(self.root, changed, 'new host', self.runner)

    def test_corrupt_source_and_patch_reject_before_extraction_or_build(self):
        for path in [self.archive, self.patch]:
            original = path.read_bytes()
            path.write_bytes(original + b'changed')
            with self.subTest(path=path.name), self.assertRaises(RuntimeError):
                prepare_source(self.root, self.pins, self.runner)
            self.assertFalse((self.root / 'toolchains/gcc302-source').exists())
            self.assertEqual(self.commands, [])
            path.write_bytes(original)

    def test_archive_path_escape_and_symlinks_reject_before_extraction(self):
        for name, kind in [('gcc-3.0.2/../../escape', tarfile.REGTYPE),
                           ('/gcc-3.0.2/absolute', tarfile.REGTYPE),
                           ('gcc-3.0.2/link', tarfile.SYMTYPE)]:
            archive = self.root / 'bad.tar.gz'
            with tarfile.open(archive, 'w:gz') as stream:
                info = tarfile.TarInfo(name)
                info.type = kind
                info.linkname = '../../escape'
                stream.addfile(info)
            output = self.root / 'out'
            output.mkdir(exist_ok=True)
            with self.subTest(name=name), self.assertRaisesRegex(RuntimeError, 'archive entry'):
                extract_source(archive, output, '3.0.2')
            self.assertEqual(list(output.iterdir()), [])


try:
    from pilot import compile_function
except ModuleNotFoundError as error:
    if error.name != 'elftools':
        raise
    compile_function = None


@unittest.skipUnless(compile_function is not None and
                     (ROOT / 'toolchains/gcc302-build/gcc/cc1').is_file() and
                     (ROOT / 'toolchains/binutils/bin/arm-none-eabi-as').is_file(),
                     'Native source fixture requires separately provisioned GCC302; no ROM is needed')
class CompilerSourceFixtureTests(unittest.TestCase):
    def test_invalid_selection_rejects_before_running_any_native_tool(self):
        with tempfile.TemporaryDirectory() as scratch:
            root = Path(scratch).resolve()
            source = root / 'fixture.c'
            source.write_text('unsigned int compiler_fixture(void) {return 1;}\n')
            function = {'name': 'compiler_fixture', 'rom_offset': 0x1000, 'size': 16,
                        'compiler_id': 'unknown'}
            with patch('pilot.run') as run:
                with self.assertRaisesRegex(ValueError, 'Unknown'):
                    compile_function(function, source, root / 'out', ['-O2'], copies=[])
                run.assert_not_called()

    def test_selected_backend_links_both_modes_and_changed_source_propagates(self):
        with tempfile.TemporaryDirectory() as scratch:
            root = Path(scratch).resolve()
            for mode, flag in [('Thumb', '-mthumb'), ('ARM', '-marm')]:
                function = {'name': 'compiler_fixture', 'rom_offset': 0x1000,
                            'size': 16, 'mode': mode, 'compiler_id': 'gcc302',
                            'compiler_flags': ['-O3', flag, '-mthumb-interwork']}
                source = root / (mode + '.c')
                source.write_text('unsigned int compiler_fixture(unsigned int value) { return value+7; }\n')
                positive, commands = compile_function(function, source, root / mode, ['-O2'], copies=[])
                self.assertEqual(commands[1][0], str(ROOT / 'toolchains/gcc302-build/gcc/cc1'))
                self.assertEqual(commands[1][1:4], function['compiler_flags'])
                changed = root / (mode + '-changed.c')
                changed.write_text(source.read_text().replace('+7', '+8'))
                negative, negative_commands = compile_function(function, changed,
                                         root / (mode + '-control'), ['-O2'], copies=[])
                self.assertEqual(negative_commands[1][0], commands[1][0])
                self.assertEqual(len(negative), len(positive))
                self.assertNotEqual(negative, positive)
            default = {'name': 'compiler_fixture', 'rom_offset': 0x1000, 'size': 16}
            _, commands = compile_function(default, source, root / 'default',
                                            ['-O2', '-mthumb-interwork'], copies=[])
            self.assertEqual(commands[1][0], str(ROOT / 'toolchains/agbcc/gcc/agbcc'))
            self.assertEqual(commands[1][1:3], ['-O2', '-mthumb-interwork'])


if __name__ == '__main__':
    unittest.main()
