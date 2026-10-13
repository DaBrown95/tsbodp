"""The optional HWI32 compiler keeps its own pins and rejects stale inputs."""
import copy
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import test_compiler_selection as ordinary_tests
from setup_gcc302 import provision
from toolchain import (GCC302_HWI32_PIN, GCC302_HWI32_PROFILE, GCC302_PROFILE,
                       compiler_selection, load_profile, verify_native)


class Hwi32SelectionTests(unittest.TestCase):
    def test_separate_profile_and_explicit_modes(self):
        for mode, flag in [('Thumb', '-mthumb'), ('ARM', '-marm')]:
            selected = compiler_selection({'compiler_id': 'gcc302_hwi32',
                'mode': mode, 'compiler_flags': ['-O3', flag]}, [])
            self.assertEqual(selected['pin'], GCC302_HWI32_PIN)
            self.assertEqual(selected['profile'], GCC302_HWI32_PROFILE)
            self.assertEqual(selected['executable'],
                             Path('toolchains/gcc302-hwi32-build/gcc/cc1'))
            with self.assertRaisesRegex(ValueError, 'explicit'):
                compiler_selection({'compiler_id': 'gcc302_hwi32', 'mode': mode}, ['-O3'])
            with self.assertRaises(ValueError):
                compiler_selection({'compiler_id': 'gcc302_hwi32', 'mode': mode},
                                   ['-O3', '-mthumb', '-marm'])


class Hwi32ProvisionTests(unittest.TestCase):
    def fixture(self):
        fixture = ordinary_tests.Gcc302ProvisionTests()
        fixture.setUp()
        self.addCleanup(fixture.doCleanups)
        fixture.name = 'toolchains/gcc302-hwi32-build/gcc/cc1'
        fixture.pins['native_tool_sha256'] = {fixture.name: '0' * 64}
        for field in ('source_directory', 'build_directory', 'install_directory'):
            fixture.pins['compiler'][field] = fixture.pins['compiler'][field].replace(
                'gcc302-', 'gcc302-hwi32-')
        fixture.pin_path = fixture.root / GCC302_HWI32_PIN
        fixture.pin_path.write_text(json.dumps(fixture.pins))
        return fixture

    def build(self, fixture):
        return provision(fixture.root, fixture.pins, 'new host', fixture.runner,
                         GCC302_HWI32_PIN, GCC302_HWI32_PROFILE)

    def test_fresh_build_is_separate_and_all_changed_inputs_reject(self):
        fixture = self.fixture()
        public_pin = fixture.pin_path.read_bytes()
        self.assertTrue(self.build(fixture))
        self.assertEqual(fixture.pin_path.read_bytes(), public_pin)
        self.assertFalse((fixture.root / GCC302_PROFILE).exists())
        lock, local = load_profile(fixture.root, GCC302_HWI32_PIN, GCC302_HWI32_PROFILE)
        self.assertEqual(local, GCC302_HWI32_PROFILE)
        verify_native(fixture.root, lock, 'new host')
        self.assertFalse(self.build(fixture))
        for path in (fixture.root / fixture.name, fixture.archive, fixture.patch,
                     fixture.root / 'toolchains/gcc302-hwi32-source/main.c'):
            original = path.read_bytes()
            path.write_bytes(original + b'changed')
            with self.subTest(path=path), self.assertRaises(RuntimeError):
                self.build(fixture)
            path.write_bytes(original)
        changed = copy.deepcopy(fixture.pins)
        changed['compiler']['source_tree_sha256'] = '0' * 64
        fixture.pin_path.write_text(json.dumps(changed))
        with self.assertRaisesRegex(RuntimeError, 'stale'):
            provision(fixture.root, changed, 'new host', fixture.runner,
                      GCC302_HWI32_PIN, GCC302_HWI32_PROFILE)

    def test_unknown_binary_and_cross_profile_native_pin_reject(self):
        fixture = self.fixture()
        binary = fixture.root / fixture.name
        binary.parent.mkdir(parents=True)
        binary.write_bytes(b'unknown compiler')
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            self.build(fixture)
        self.assertFalse((fixture.root / GCC302_HWI32_PROFILE).exists())
        self.assertEqual(fixture.commands, [])
        fixture.pins['native_tool_sha256'] = {
            'toolchains/gcc302-build/gcc/cc1': '0' * 64}
        with self.assertRaisesRegex(RuntimeError, 'selected build directory'):
            self.build(fixture)
        self.assertEqual(fixture.commands, [])


@unittest.skipUnless((ROOT / 'toolchains/gcc302-hwi32-build/gcc/cc1').is_file(),
                     'Optional HWI32 compiler is not installed')
class Hwi32NativeTests(unittest.TestCase):
    def test_signed_shift_constant_is_synthesized_and_source_change_matters(self):
        import pilot
        from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB
        with tempfile.TemporaryDirectory() as temporary:
            folder = Path(temporary).resolve()
            source = folder / 'fixture.c'
            source.write_text('unsigned fixture(void) { return 0xc0000000U; }\n')
            flags = ['-O3', '-mthumb', '-mthumb-interwork', '-fomit-frame-pointer',
                     '-mcpu=arm7tdmi']
            function = {'name': 'fixture', 'rom_offset': 0x100, 'size': 8,
                        'compiler_id': 'gcc302_hwi32', 'compiler_flags': flags}
            data, commands = pilot.compile_function(function, source, folder / 'positive', flags)
            instructions = [(i.mnemonic, i.op_str) for i in
                            Cs(CS_ARCH_ARM, CS_MODE_THUMB).disasm(data, 0x08000100)]
            self.assertEqual([name for name, _ in instructions[:3]], ['movs', 'lsls', 'bx'])
            cursor, value = instructions[0][1].split(', ')
            self.assertEqual(value, '#0xc0')
            self.assertEqual(instructions[1][1], 'r0, ' + cursor + ', #0x18')
            self.assertEqual(instructions[2][1], 'lr')
            self.assertEqual(commands[1][0], str(ROOT / 'toolchains/gcc302-hwi32-build/gcc/cc1'))
            source.write_text('unsigned fixture(void) { return 0x80000000U; }\n')
            changed, _ = pilot.compile_function(function, source, folder / 'negative', flags)
            self.assertNotEqual(changed, data)


if __name__ == '__main__':
    unittest.main()
