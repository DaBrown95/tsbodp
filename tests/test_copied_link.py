"""A copied object's branch uses its execution VMA, while bytes occupy ROM LMA."""
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from toolchain import modern_assembler_abi_flags
try:
    from build_rom import link_rom
except ModuleNotFoundError as error:
    if error.name != 'elftools':
        raise
    link_rom = None


@unittest.skipUnless(link_rom is not None and
                     (ROOT / 'toolchains/binutils/bin/arm-none-eabi-as').exists(),
                     'Native linker fixture requires make setup; no ROM is needed')
class CopiedLinkTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.folder = Path(temporary.name)
        self.pilot = self.folder / 'pilot'
        objfolder = self.pilot / 'copied_code'
        objfolder.mkdir(parents=True)
        source = objfolder / 'source.s'
        source.write_text('.text\n.global copied_code\n.type copied_code,%function\n'
                          'copied_code: b branch_target\n.size copied_code,.-copied_code\n')
        subprocess.run([ROOT / 'toolchains/binutils/bin/arm-none-eabi-as',
                        '-mcpu=arm7tdmi', '--no-pad-sections', *modern_assembler_abi_flags(),
                        source, '-o', objfolder / 'source.o'], check=True)
        self.copies = [{'name': 'fixture', 'rom_offset': 16, 'ram_address': 0x03001000, 'size': 4}]
        self.manifest = {'rom_size': 32, 'functions': [{'name': 'copied_code', 'rom_offset': 16,
                         'size': 4, 'ram_address': 0x03001000, 'ram_copy': 'fixture', 'mode': 'ARM',
                         'symbols': {'branch_target': '0x03001200'}}]}
        self.expected = bytearray(range(32))
        displacement = (0x03001200 - (0x03001000 + 8)) // 4
        self.expected[16:20] = struct.pack('<I', 0xEA000000 | displacement)
        self.reference = self.folder / 'reference'
        self.reference.write_bytes(self.expected)

    def test_ram_relative_branch_is_stored_at_original_rom_offset(self):
        output, _, _ = link_rom(self.manifest, self.reference, self.pilot,
                                self.folder / 'linked', copies=self.copies)
        self.assertEqual(output.read_bytes(), self.expected)

    def test_wrong_execution_address_fails_before_linking(self):
        self.manifest['functions'][0]['ram_address'] += 4
        with self.assertRaisesRegex(ValueError, 'RAM copy'):
            link_rom(self.manifest, self.reference, self.pilot,
                     self.folder / 'wrong', copies=self.copies)

    def test_unexpected_allocated_source_data_is_rejected(self):
        objfolder = self.pilot / 'copied_code'
        source = objfolder / 'source.s'
        source.write_text(source.read_text() + '.data\n.word 123\n')
        subprocess.run([ROOT / 'toolchains/binutils/bin/arm-none-eabi-as',
                        '-mcpu=arm7tdmi', '--no-pad-sections', *modern_assembler_abi_flags(),
                        source, '-o', objfolder / 'source.o'], check=True)
        with self.assertRaisesRegex(ValueError, 'allocated source section'):
            link_rom(self.manifest, self.reference, self.pilot,
                     self.folder / 'extra-data', copies=self.copies)

    def test_incompatible_object_abi_is_rejected_by_linker(self):
        objfolder = self.pilot / 'copied_code'
        # Generate an incompatible object directly; production never rewrites
        # its flags or suppresses the linker's ABI checks.
        subprocess.run([ROOT / 'toolchains/binutils/bin/arm-none-eabi-as',
                        '-mcpu=arm7tdmi', '--no-pad-sections', '-meabi=5',
                        objfolder / 'source.s', '-o', objfolder / 'source.o'], check=True)
        with self.assertRaisesRegex(RuntimeError, 'EABI version'):
            link_rom(self.manifest, self.reference, self.pilot,
                     self.folder / 'wrong-abi', copies=self.copies)

    def test_wrong_copied_callee_alias_rejects_before_assembler_or_linker_runs(self):
        self.manifest['functions'][0]['symbols']['copied_code'] = '0x08000010'
        with patch('build_rom.run') as run:
            with self.assertRaisesRegex(ValueError, 'execution address'):
                link_rom(self.manifest, self.reference, self.pilot,
                         self.folder / 'wrong-callee', copies=self.copies)
            run.assert_not_called()
