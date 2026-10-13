"""Native C candidates must not hide allocated storage outside their text."""
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
try:
    from pilot import compile_function
except ModuleNotFoundError as error:
    if error.name != 'elftools':
        raise
    compile_function = None


@unittest.skipUnless(compile_function and shutil.which('xcrun') and
                     (ROOT / 'toolchains/agbcc/gcc/agbcc').is_file() and
                     (ROOT / 'toolchains/binutils/bin/arm-none-eabi-as').is_file(),
                     'Native C fixtures require make setup; no ROM is needed')
class PilotAllocatedTests(unittest.TestCase):
    def candidate(self, source, flags):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        folder = Path(temporary.name).resolve()
        path = folder / 'source.c'
        path.write_text(source)
        function = {'name': 'fixture', 'rom_offset': 0, 'size': 4,
                    'symbols': {'fixture_value': '0x03000000'}}
        return compile_function(function, path, folder / 'proof', flags, copies=[])

    def test_referenced_string_storage_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'allocated source section'):
            self.candidate('const char *fixture(void) { return "fixture"; }\n',
                           ['-O2', '-mthumb-interwork'])

    def test_private_mutable_storage_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'allocated source section'):
            self.candidate('static unsigned int counter;\n'
                           'unsigned int fixture(void) { return ++counter; }\n',
                           ['-O2', '-mthumb-interwork'])

    def test_unused_o1_symbol_pool_is_rejected(self):
        # This backend emits an unused .LC address word after moving the
        # referenced address into a Thumb text literal pool at -O1.
        with self.assertRaisesRegex(ValueError, 'allocated source section'):
            self.candidate('extern unsigned int fixture_value;\n'
                           'unsigned int *fixture(void) { return &fixture_value; }\n',
                           ['-O1', '-mthumb-interwork'])

    def test_nonstorage_numeric_address_view_passes(self):
        data, commands = self.candidate(
            'unsigned int *fixture(void) { return (unsigned int *)0x03000000; }\n',
            ['-O1', '-mthumb-interwork'])
        self.assertTrue(data)
        self.assertTrue(commands)
