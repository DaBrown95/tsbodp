"""A ported extent must differ from its source only in solved relocation fields."""
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import port_target
from ram_copies import validate_copy


def thumb_bl(source, target):
    delta = (target - (source + 4)) >> 1
    return struct.pack('<HH', 0xF000 | ((delta >> 11) & 0x7ff), 0xF800 | (delta & 0x7ff))


class CompareTests(unittest.TestCase):
    """Two 8-byte extents: a literal word and a Thumb call, both relocated."""

    def setUp(self):
        self.function = {'name': 'f', 'size': 8,
                         'symbols': {'g_word': '0x03002180', 'callee': '0x08001001'}}
        self.old = bytearray(0x200)
        self.new = bytearray(0x200)
        self.o0, self.o1 = 0x100, 0x140
        struct.pack_into('<I', self.old, self.o0, 0x03002180)
        struct.pack_into('<I', self.new, self.o1, 0x03002170)
        self.old[self.o0 + 4:self.o0 + 8] = thumb_bl(0x08000000 + self.o0 + 4, 0x08001000)
        self.new[self.o1 + 4:self.o1 + 8] = thumb_bl(0x08000000 + self.o1 + 4, 0x08001020)
        self.relocations = [(0, port_target.R_ARM_ABS32, 'g_word', True),
                            (4, port_target.R_ARM_THM_CALL, 'callee', True)]

    def compare(self, relocations=None):
        with mock.patch.object(port_target, 'relocations',
                               return_value=relocations or self.relocations):
            return port_target.compare(self.function, self.o0, self.o1, bytes(self.old),
                                       bytes(self.new), None, self.o1 - self.o0)

    def test_relocated_fields_are_solved(self):
        solved, reason = self.compare()
        self.assertIsNone(reason)
        self.assertEqual(solved, {'g_word': 0x03002170, 'callee': 0x08001021})

    def test_unrelocated_byte_change_is_rejected(self):
        # A hard-coded constant without a relocation must not be carried over.
        solved, reason = self.compare([self.relocations[1]])
        self.assertIsNone(solved)
        self.assertIn('non-relocation bytes differ', reason)

    def test_same_symbol_solved_two_ways_is_rejected(self):
        relocations = [(0, port_target.R_ARM_ABS32, 'callee', True),
                       (4, port_target.R_ARM_THM_CALL, 'callee', True)]
        self.function['symbols']['callee'] = '0x03002180'
        solved, reason = self.compare(relocations)
        self.assertIsNone(solved)
        self.assertIn('inconsistently', reason)

    def test_section_relative_word_must_move_with_the_extent(self):
        relocations = [(0, port_target.R_ARM_ABS32, '.text', False),
                       self.relocations[1]]
        solved, reason = self.compare(relocations)
        self.assertIsNone(solved)
        self.assertIn('section-relative', reason)


class CarryTests(unittest.TestCase):
    """Only functions missing from the destination are added; existing entries stay."""

    def setUp(self):
        self.source = {'functions': [
            {'name': 'kept', 'rom_offset': 0x100, 'size': 8, 'symbols': {}},
            {'name': 'new', 'rom_offset': 0x200, 'size': 8,
             'symbols': {'g_word': '0x03002180', 'kept': '0x08000101'}}]}
        self.destination = {'functions': [
            {'name': 'kept', 'rom_offset': 0x180, 'size': 12, 'symbols': {'g_word': '0x03002170'}}]}

    def carry(self, solved):
        return port_target.carry(self.source, self.destination, {},
                                 {'kept': 0x140, 'new': 0x240},
                                 lambda f, offset, moved: (solved, None))

    def test_new_function_is_added_and_existing_entry_is_untouched(self):
        additions, rejected = self.carry({'g_word': 0x03002170})
        self.assertEqual(rejected, {})
        self.assertEqual([f['name'] for f in additions['functions']], ['new'])
        added = additions['functions'][0]
        self.assertEqual(added['rom_offset'], 0x240)
        # An unreferenced alias takes the destination's own definition.
        self.assertEqual(added['symbols'], {'g_word': '0x03002170', 'kept': '0x08000181'})
        self.assertEqual(self.destination['functions'][0]['rom_offset'], 0x180)

    def test_symbol_disagreeing_with_destination_is_rejected(self):
        additions, rejected = self.carry({'g_word': 0x03002160})
        self.assertEqual(additions['functions'], [])
        self.assertIn('disagrees', rejected['new'])


class DmaCopyTests(unittest.TestCase):
    def test_moved_dma_literals_are_checked_at_their_new_offset(self):
        copy = {'rom_offset': 0x160, 'ram_address': 0x03001b90, 'size': 512,
                'dma_literal_offset': 0x1f924}
        words = {0x1f924: 0x08000160, 0x1f928: 0x03001b90, 0x1f92c: 0x84000080}
        validate_copy(copy, words.__getitem__)
        with self.assertRaises(KeyError):
            validate_copy({**copy, 'dma_literal_offset': 0x1f88c}, words.__getitem__)


if __name__ == '__main__':
    unittest.main()
