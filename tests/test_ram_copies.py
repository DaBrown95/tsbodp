"""A wrong copied address, mode or count must never become a trusted RAM map."""
import sys
from pathlib import Path
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from ram_copies import validate_copy


class CopyTests(unittest.TestCase):
    def setUp(self):
        self.copy = {'rom_offset': 0xb840, 'ram_address': 0x03002900, 'size': 284,
                     'word_copy_literal_offsets': [4, 8, 12], 'word_copy_control': 0x04000047}
        self.words = {4: 0x0800b840, 8: 0x03002900, 12: 0x04000047}

    def test_fixed_word_copy(self):
        validate_copy(self.copy, self.words.__getitem__)

    def test_changed_source_destination_or_control_rejected(self):
        for offset in self.words:
            words = {**self.words, offset: self.words[offset] + 4}
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                validate_copy(self.copy, words.__getitem__)

    def test_wrong_count_halfword_or_fill_mode_rejected(self):
        for change in ({'size': 280}, {'size': 0}, {'word_copy_control': 0x47},
                       {'word_copy_control': 0x05000047}):
            with self.subTest(change=change), self.assertRaises(ValueError):
                validate_copy({**self.copy, **change}, self.words.__getitem__)
