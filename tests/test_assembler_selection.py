"""Historical assembly is explicitly selected, pinned, and never rewritten."""
import copy
import hashlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tarfile
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from toolchain import (PROFILE, BINUTILS2101_PIN, BINUTILS2101_PROFILE,
                       assembler_selection, load_profile, sha, source_tree_sha256,
                       verify_binutils2101_source, verify_native, modern_assembler_abi_flags)
from setup_binutils2101 import provision


class AssemblerSelectionTests(unittest.TestCase):
    def test_modern_tool_and_generation_flags_are_retained_with_explicit_gnu_abi(self):
        for mode, flags in [('Thumb', ['-mcpu=arm7tdmi', '-mthumb', '--no-pad-sections']),
                            ('ARM', ['-mcpu=arm7tdmi', '--no-pad-sections'])]:
            selected = assembler_selection({'mode': mode})
            self.assertEqual(selected['executable'], Path('toolchains/binutils/bin/arm-none-eabi-as'))
            self.assertEqual(selected['source_flags'], [*flags, '-meabi=gnu', '-mfpu=softfpa'])
            self.assertEqual(selected['extern_flags'], modern_assembler_abi_flags())

    def test_historical_source_and_external_objects_share_soft_float_convention(self):
        for mode in ('Thumb', 'ARM'):
            selected = assembler_selection({'mode': mode, 'assembler_id': 'binutils2101'})
            self.assertEqual(selected['pin'], BINUTILS2101_PIN)
            self.assertEqual(selected['source_flags'], selected['extern_flags'])
            self.assertEqual(selected['source_flags'][:2], ['-marm7tdmi', '-mno-fpu'])
            self.assertEqual('-mthumb' in selected['source_flags'], mode == 'Thumb')
            self.assertNotIn('--no-pad-sections', selected['source_flags'])

    def test_unknown_tool_paths_and_modes_reject(self):
        for function in ({'assembler_id': '../untrusted'}, {'assembler_id': None},
                         {'mode': 'unknown'}, {'assembler_id': 'binutils2101', 'mode': 'unknown'}):
            with self.subTest(function=function), self.assertRaises(ValueError):
                assembler_selection(function)


class Binutils2101ProvisionTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        for name in ('toolchains', 'config', 'tools'):
            (self.root / name).mkdir()
        self.patch = self.root / 'tools/compat.patch'
        self.patch.write_bytes(b'pinned declaration patch')
        self.archive = self.root / 'toolchains/binutils-2.10.1.tar.gz'
        with tarfile.open(self.archive, 'w:gz') as stream:
            info = tarfile.TarInfo('binutils-2.10.1/main.c')
            info.size = 8
            stream.addfile(info, io.BytesIO(b'original'))
        expected = self.root / 'expected'
        expected.mkdir()
        (expected / 'main.c').write_bytes(b'patched')
        self.name = 'toolchains/binutils2101-build/gas/as-new'
        self.pins = {'assembler': {'source_url': 'https://example.invalid/binutils-2.10.1.tar.gz',
            'source_version': '2.10.1', 'source_sha256': sha(self.archive),
            'compatibility_patch': 'tools/compat.patch', 'compatibility_patch_sha256': sha(self.patch),
            'source_directory': 'toolchains/binutils-2.10.1',
            'source_tree_sha256': source_tree_sha256(expected),
            'build_directory': 'toolchains/binutils2101-build',
            'install_directory': 'toolchains/binutils2101-install',
            'configure_environment': ['CC=clang', 'CFLAGS=-std=gnu89', 'ac_cv_exeext='],
            'configure_options': ['--target=arm-elf'], 'build_options': ['all-gas']},
            'native_tool_sha256': {self.name: hashlib.sha256(b'original native').hexdigest()},
            'host_clang': 'original host'}
        self.pin_path = self.root / BINUTILS2101_PIN
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

    def test_fresh_build_enrolls_an_independent_profile_without_altering_public_pin(self):
        before = self.pin_path.read_bytes()
        self.assertTrue(provision(self.root, self.pins, 'new host', self.runner))
        self.assertEqual(self.pin_path.read_bytes(), before)
        lock, local = load_profile(self.root, BINUTILS2101_PIN, BINUTILS2101_PROFILE)
        self.assertEqual(local, BINUTILS2101_PROFILE)
        self.assertEqual(lock['assembler'], self.pins['assembler'])
        verify_native(self.root, lock, 'new host')
        verify_binutils2101_source(self.root, lock)
        self.assertFalse((self.root / PROFILE).exists())
        self.assertFalse(provision(self.root, self.pins, 'new host', self.runner))
        self.assertEqual(len(self.commands), 3)
        self.assertIn('ac_cv_exeext=', self.commands[1])

    def test_unknown_binary_and_incomplete_build_cannot_be_adopted(self):
        binary = self.root / self.name
        binary.parent.mkdir(parents=True)
        binary.write_bytes(b'unknown native')
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            provision(self.root, self.pins, 'original host', self.runner)
        self.assertFalse((self.root / BINUTILS2101_PROFILE).exists())
        binary.unlink()
        with self.assertRaisesRegex(RuntimeError, 'Incomplete'):
            provision(self.root, self.pins, 'original host', self.runner)
        self.assertEqual(self.commands, [])

    def test_missing_pin_binary_or_changed_host_reject(self):
        self.pin_path.unlink()
        with self.assertRaises(FileNotFoundError):
            load_profile(self.root, BINUTILS2101_PIN, BINUTILS2101_PROFILE)
        self.pin_path.write_text(json.dumps(self.pins))
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            verify_native(self.root, self.pins, 'original host')
        provision(self.root, self.pins, 'new host', self.runner)
        with self.assertRaisesRegex(RuntimeError, 'preprocessor'):
            provision(self.root, self.pins, 'changed host', self.runner)
        (self.root / self.name).unlink()
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            provision(self.root, self.pins, 'new host', self.runner)

    def test_stale_pins_and_changed_inputs_reject_after_setup(self):
        provision(self.root, self.pins, 'new host', self.runner)
        for path in (self.root / self.name, self.patch, self.archive,
                     self.root / 'toolchains/binutils-2.10.1/main.c'):
            original = path.read_bytes()
            path.write_bytes(original + b'changed')
            with self.subTest(path=path.name), self.assertRaises(RuntimeError):
                provision(self.root, self.pins, 'new host', self.runner)
            path.write_bytes(original)
        changed = copy.deepcopy(self.pins)
        changed['assembler']['source_version'] = 'different'
        self.pin_path.write_text(json.dumps(changed))
        with self.assertRaisesRegex(RuntimeError, 'stale'):
            provision(self.root, changed, 'new host', self.runner)

    def test_corrupt_archive_and_patch_reject_before_build(self):
        for path in (self.archive, self.patch):
            original = path.read_bytes()
            path.write_bytes(original + b'changed')
            with self.subTest(path=path.name), self.assertRaises(RuntimeError):
                provision(self.root, self.pins, 'new host', self.runner)
            self.assertEqual(self.commands, [])
            self.assertFalse((self.root / 'toolchains/binutils-2.10.1').exists())
            path.write_bytes(original)


try:
    from pilot import compile_function, assemble_glue
    from build_rom import link_rom
    from elftools.elf.elffile import ELFFile
except ModuleNotFoundError as error:
    if error.name != 'elftools':
        raise
    compile_function = None


@unittest.skipUnless(compile_function is not None and
                     (ROOT / 'toolchains/gcc302-build/gcc/cc1').is_file() and
                     (ROOT / 'toolchains/binutils2101-build/gas/as-new').is_file() and
                     (ROOT / 'toolchains/binutils/bin/arm-none-eabi-as').is_file(),
                     'Native fixture needs separately provisioned tools; no game inputs are used')
class HistoricalAssemblerSourceTests(unittest.TestCase):
    def test_invalid_assembler_rejects_before_any_native_command(self):
        with tempfile.TemporaryDirectory() as scratch:
            root = Path(scratch).resolve()
            source = root / 'fixture.c'
            source.write_text('unsigned int assembler_fixture(void) {return 1;}\n')
            function = {'name': 'assembler_fixture', 'rom_offset': 8, 'size': 16,
                        'assembler_id': 'unknown'}
            with patch('pilot.run') as run:
                with self.assertRaisesRegex(ValueError, 'Unknown'):
                    compile_function(function, source, root / 'out', ['-O2'], copies=[])
                run.assert_not_called()

    def test_unchanged_compiler_assembly_has_historical_zero_alignment_and_links_with_modern_gaps(self):
        with tempfile.TemporaryDirectory() as scratch:
            root = Path(scratch).resolve()
            source = root / 'fixture.c'
            source.write_text('unsigned int assembler_fixture(unsigned int value) {return value == 0;}\n')
            function = {'name': 'assembler_fixture', 'rom_offset': 8, 'size': 20,
                        'compiler_id': 'gcc302', 'assembler_id': 'binutils2101',
                        'compiler_flags': ['-O3', '-mthumb', '-mthumb-interwork']}
            pilot_folder = root / 'pilot'
            old, old_commands = compile_function(function, source, pilot_folder / function['name'], [], copies=[])
            modern, _ = compile_function({**function, 'assembler_id': 'binutils'}, source, root / 'modern', [], copies=[])
            self.assertEqual((pilot_folder / function['name'] / 'source.s').read_bytes(),
                             (root / 'modern/source.s').read_bytes())
            self.assertEqual(len(old), 20)
            self.assertEqual(old[:-2], modern[:-2])
            self.assertEqual(old[-2:], b'\0\0')
            self.assertEqual(modern[-2:], b'\xc0\x46')
            # The explicit GNU ABI changes metadata, not instruction bytes.
            original_obj = root / 'original-eabi5.o'
            subprocess.run([ROOT / 'toolchains/binutils/bin/arm-none-eabi-as',
                            '-mcpu=arm7tdmi', '-mthumb', '--no-pad-sections',
                            root / 'modern/source.s', '-o', original_obj], check=True,
                           capture_output=True)
            with original_obj.open('rb') as stream:
                elf = ELFFile(stream)
                original_text = elf.get_section_by_name('.text').data()
                self.assertEqual(elf['e_flags'] >> 24, 5)
            with (root / 'modern/source.o').open('rb') as stream:
                elf = ELFFile(stream)
                self.assertEqual(elf.get_section_by_name('.text').data(), original_text)
                self.assertEqual(elf['e_flags'] >> 24, 0)
            for command in (old_commands[2], old_commands[3]):
                self.assertEqual(command[1:3], ['-marm7tdmi', '-mno-fpu'])
            modern_source = root / 'modern-fixture.c'
            modern_source.write_text('unsigned int modern_fixture(unsigned int value) {return value + 9;}\n')
            modern_function = {'name': 'modern_fixture', 'rom_offset': 28, 'size': 4}
            modern_c, _ = compile_function(modern_function, modern_source,
                                          pilot_folder / 'modern_fixture',
                                          ['-O2', '-mthumb-interwork'], copies=[])
            self.assertEqual(len(modern_c), 4)
            glue_source = root / 'glue.s'
            glue_source.write_text('.text\n.thumb\n.thumb_func\n.global fixture_glue\n'
                                   'fixture_glue:\nmovs r0, #7\nbx lr\n')
            glue = {'name': 'fixture_glue', 'rom_offset': 32, 'size': 4,
                    'kind': 'assembly_glue'}
            glue_bytes, _ = assemble_glue(glue, glue_source, pilot_folder / 'fixture_glue')
            self.assertEqual(len(glue_bytes), 4)
            reference = root / 'synthetic.bin'
            expected = bytes(range(8)) + old + modern_c + glue_bytes + bytes(range(4))
            reference.write_bytes(expected)
            output, regions, commands = link_rom({'functions': [function, modern_function],
                                                  'assembly': [glue], 'rom_size': len(expected)},
                                                 reference, pilot_folder, root / 'whole', copies=[])
            self.assertEqual(output.read_bytes(), expected)
            self.assertEqual([region['kind'] for region in regions],
                             ['unconverted', 'compiled_c', 'compiled_c', 'assembly_glue', 'unconverted'])
            self.assertTrue(any(command[0].endswith('arm-none-eabi-as') for command in commands))

    def test_changed_source_propagates_in_thumb_and_arm(self):
        with tempfile.TemporaryDirectory() as scratch:
            root = Path(scratch).resolve()
            source = root / 'fixture.c'
            source.write_text('unsigned int assembler_fixture(unsigned int value) {return value + 7;}\n')
            changed = root / 'changed.c'
            changed.write_text(source.read_text().replace('+ 7', '+ 8'))
            for mode, flag in [('Thumb', '-mthumb'), ('ARM', '-marm')]:
                function = {'name': 'assembler_fixture', 'rom_offset': 8, 'size': 16, 'mode': mode,
                            'compiler_id': 'gcc302', 'assembler_id': 'binutils2101',
                            'compiler_flags': ['-O3', flag, '-mthumb-interwork']}
                positive, _ = compile_function(function, source, root / mode, [], copies=[])
                negative, _ = compile_function(function, changed, root / (mode + '-control'), [], copies=[])
                self.assertEqual(len(positive), len(negative))
                self.assertNotEqual(positive, negative)


if __name__ == '__main__':
    unittest.main()
