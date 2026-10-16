"""Calibrate the optional mGBA observer with original, synthetic test code."""
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
MGBA_SOURCE = ROOT / 'toolchains/mgba-source'
MGBA_BUILD = ROOT / 'toolchains/mgba-build'


@unittest.skipUnless((MGBA_BUILD / 'libmgba.a').is_file(),
                     'optional pinned mGBA static core is not built')
class BootObserverTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory()
        cls.directory = Path(cls.temp.name)
        cls.observer = cls.directory / 'observe_boot'
        command = ['cc', '-std=c11', '-Os', '-DBUILD_STATIC',
                   '-I' + str(MGBA_SOURCE / 'include'),
                   '-I' + str(MGBA_BUILD / 'include'),
                   str(ROOT / 'tools/observe_boot.c'),
                   str(MGBA_BUILD / 'libmgba.a')]
        command += ['-framework', 'Foundation'] if sys.platform == 'darwin' else ['-lpthread']
        subprocess.run(command + ['-lm', '-o', str(cls.observer)], check=True,
                       capture_output=True)
        # Authored fixture: branch to C0, load two literals, store one word with
        # STM, then loop. These opcodes are not extracted from a game ROM.
        image = bytearray(0x1000)
        struct.pack_into('<I', image, 0, 0xEA00002E)
        struct.pack_into('<6I', image, 0xC0, 0xE59F0008, 0xE59F1008,
                         0xE8A10001, 0xEAFFFFFE, 0x12345678, 0x0300004C)
        cls.rom = cls.directory / 'authored-observer-fixture.gba'
        cls.rom.write_bytes(image)

    @classmethod
    def tearDownClass(cls):
        cls.temp.cleanup()

    def observe(self, shift=0):
        result = subprocess.run([str(self.observer), str(self.rom), '1', '20', str(shift)],
                                check=True, capture_output=True, text=True)
        return [json.loads(line) for line in result.stdout.splitlines()]

    def test_stm_payload_uses_readback_not_shim_placeholder(self):
        rows = self.observe()
        writes = [r for r in rows if r['event'] == 'pre_write']
        self.assertEqual(len(writes), 1)
        self.assertEqual(writes[0]['address'], 0x0300004C)
        self.assertEqual(writes[0]['shim_old_value'], 0)
        self.assertEqual(writes[0]['shim_proposed_value_untrusted'], 0)
        readbacks = [r for r in rows if r['event'] == 'after_step_readback']
        self.assertEqual(readbacks[0]['pre_write_event'], writes[0]['event_index'])
        self.assertEqual(readbacks[0]['word'], 0x12345678)
        self.assertEqual(rows[-1]['reason'], 'step_limit')

    def test_wrong_aligned_watch_address_does_not_report_store(self):
        positive, negative = self.observe(), self.observe(0x10000000)
        self.assertFalse(any(r['event'] == 'pre_write' for r in negative))
        for key in ('steps', 'ticks', 'frame', 'raw_pc', 'r', 'entries'):
            self.assertEqual(positive[-1][key], negative[-1][key])

    def test_entry_observation_precedes_fixture_load(self):
        reset = next(r for r in self.observe() if r.get('name') == 'reset')
        self.assertEqual(reset['raw_pc'], 0x080000C4)
        self.assertEqual(reset['r'][0:2], [0, 0])
        self.assertEqual(reset['instruction_word'], 0xE59F0008)

    def test_missing_rom_fails_without_observations(self):
        result = subprocess.run([str(self.observer), str(self.directory / 'absent.gba'),
                                 '1', '20', '0'], capture_output=True)
        self.assertEqual(result.returncode, 4)
        self.assertEqual(result.stdout, b'')

    def test_invalid_bounds_fail_before_rom_loading(self):
        for args in [('0', '20', '0'), ('-1', '20', '0'),
                     ('3601', '20', '0'), ('1', '100000001', '0'),
                     ('1', '0', '0'), ('1', '20suffix', '0'),
                     ('1', '20', '1')]:
            with self.subTest(args=args):
                result = subprocess.run([str(self.observer), str(self.rom), *args],
                                        capture_output=True)
                self.assertEqual(result.returncode, 2)
                self.assertEqual(result.stdout, b'')


if __name__ == '__main__':
    unittest.main()
