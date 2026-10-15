"""Constant-flow rejection tests using synthetic ARM7 Thumb instructions."""
import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
try:
    from inventory_rom import Scanner, BASE
    from fixed_target_proof import prove_fixed_target
except ModuleNotFoundError:
    Scanner = None


@unittest.skipIf(Scanner is None, 'Capstone is needed for constant-flow controls')
class FixedTargetProofTests(unittest.TestCase):
    def fixture(self, words, literals=None, size=0x50):
        data = bytearray(0x100)
        for off, word in words.items():
            struct.pack_into('<H', data, off, word)
        for off, value in (literals or {}).items():
            struct.pack_into('<I', data, off, value)
        for off, reg in ((0x70, 9), (0x74, 10), (0x78, 0)):
            struct.pack_into('<H', data, off, 0x4700 | reg << 3)
        struct.pack_into('<H', data, 0x60, 0x4770)  # ordinary returning callee
        scanner = Scanner(bytes(data), [])
        scanner.seed(BASE, 'Thumb', 'bounded audit')
        scanner.drain()
        return scanner, dict(rom_offset=0, size=size, name='synthetic')

    def bl(self, off, dest):
        delta = dest - off - 4
        return {off: 0xf000 | (delta >> 12 & 0x7ff),
                off + 2: 0xf800 | (delta >> 1 & 0x7ff)}

    def test_high_register_constant_survives_calls_and_loop(self):
        words = {0: 0xb500, 2: 0x480f, 4: 0x4681, 6: 0x2202,
                 12: 0x3a01, 14: 0xd1fb, 20: 0xbc01, 22: 0x4700}
        words.update(self.bl(8, 0x60)); words.update(self.bl(16, 0x70))
        s, owner = self.fixture(words, {0x40: BASE + 0x91})
        proof = prove_fixed_target(s, owner, 16, BASE + 0x91)
        self.assertEqual(proof['call_register'], 'sb')

    def test_caller_saved_constant_does_not_survive_call(self):
        words = {0: 0xb500, 2: 0x480f, 12: 0xbc01, 14: 0x4700}
        words.update(self.bl(4, 0x60)); words.update(self.bl(8, 0x78))
        s, owner = self.fixture(words, {0x40: BASE + 0x91})
        with self.assertRaisesRegex(ValueError, 'unknown or conflicts'):
            prove_fixed_target(s, owner, 8, BASE + 0x91)

    def branch_fixture(self, second):
        # Both branch paths reach the same call; one overwrites the high reg.
        words = {0: 0xb500, 2: 0x480f, 4: 0x4681, 6: 0x2900,
                 8: 0xd001, 10: 0x480e, 12: 0x4681,
                 18: 0xbc01, 20: 0x4700}
        words.update(self.bl(14, 0x70))
        return self.fixture(words, {0x40: BASE + 0x91, 0x44: second})

    def test_conflicting_branch_rejects_shared_value_passes(self):
        s, owner = self.branch_fixture(BASE + 0x95)
        with self.assertRaisesRegex(ValueError, 'unknown or conflicts'):
            prove_fixed_target(s, owner, 14, BASE + 0x91)
        s, owner = self.branch_fixture(BASE + 0x91)
        self.assertEqual(prove_fixed_target(s, owner, 14, BASE + 0x91)['target'],
                         BASE + 0x90)

    def test_swapping_two_real_transfer_sites_rejects(self):
        words = {0: 0xb500, 2: 0x480f, 4: 0x4681, 6: 0x480f,
                 8: 0x4682, 18: 0xbc01, 20: 0x4700}
        words.update(self.bl(10, 0x70)); words.update(self.bl(14, 0x74))
        s, owner = self.fixture(words, {0x40: BASE + 0x91, 0x44: BASE + 0x95})
        self.assertEqual(prove_fixed_target(s, owner, 10, BASE + 0x91)['target'],
                         BASE + 0x90)
        with self.assertRaisesRegex(ValueError, 'unknown or conflicts'):
            prove_fixed_target(s, owner, 14, BASE + 0x91)
        self.assertEqual(prove_fixed_target(s, owner, 14, BASE + 0x95)['target'],
                         BASE + 0x94)

    def test_unowned_site_or_noncall_rejects(self):
        s, owner = self.fixture({0: 0x4770})
        for site in (0, 2, 0x70):
            with self.subTest(site=site), self.assertRaises(ValueError):
                prove_fixed_target(s, owner, site, BASE + 0x91)

    def test_external_branch_and_service_fail_closed(self):
        for middle in ({6: 0xdf00}, {6: 0x2900, 8: 0xd12a}):
            call = 10 if 8 in middle else 8
            words = {0: 0xb500, 2: 0x480f, 4: 0x4681,
                     call + 4: 0xbc01, call + 6: 0x4700, **middle}
            words.update(self.bl(call, 0x70))
            s, owner = self.fixture(words, {0x40: BASE + 0x91})
            with self.assertRaises(ValueError):
                prove_fixed_target(s, owner, call, BASE + 0x91)


if __name__ == '__main__':
    unittest.main()
