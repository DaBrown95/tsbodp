"""Synthetic saved-byte dispatches keep ownership separate from runtime validity.

The labelled Thumb program and address words are authored here without game
bytes. Its read window deliberately includes disabled words with nonzero high
flag bytes, ARM and Thumb C entries, and unaligned raw region-00 operands.
"""
import copy
import hashlib
import importlib.util
import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))

HAS_CAPSTONE = importlib.util.find_spec('capstone') is not None
if HAS_CAPSTONE:
    from bounded_indirect import (BASE, OPERAND_PROOF_KIND,
                                  validate_saved_volume_operands,
                                  annotate_operand_records)
    from inventory_rom import Scanner, unresolved_callback_sites


def digest(data):
    return hashlib.sha256(data).hexdigest()


class SavedByteFixture:
    def __init__(self):
        self.data = bytearray(0x500)
        self.pc, self.labels, self.fixups = 0, {}, []
        self.emit('entry', 0xb500)           # push {lr}
        self.emit('entry_test', 0x2f00)      # cmp r7, #0
        self.branch('entry_branch', 'finish')
        self.emit('entry_noop', 0x46c0)      # mov r8, r8
        self.emit('start', 0x1c22)           # adds r2, r4, #0
        self.emit('field', 0x325d)           # adds r2, #93
        self.emit('load', 0x7810)            # ldrb r0, [r2]
        self.emit('narrow', 0x0603)          # lsls r3, r0, #24
        self.emit('zero_test', 0x2b00)       # cmp r3, #0
        self.branch('zero_branch', 'finish')
        self.emit('select', 0x0f18)          # lsrs r0, r3, #28
        self.emit('stride', 0x00c2)          # lsls r2, r0, #3
        self.emit('literal_load', 0)
        self.emit('flag_address', 0x1d13)    # adds r3, r2, #4
        self.emit('flag_load', 0x5cc8)       # ldrb r0, [r1, r3]
        self.emit('flag_test', 0x2800)       # cmp r0, #0
        self.branch('flag_branch', 'finish')
        self.emit('capture', 0x588b)         # ldr r3, [r1, r2]
        self.emit('argument', 0x1c20)        # adds r0, r4, #0
        self.emit('row_argument', 0x2100)    # movs r1, #0
        self.emit('call', 0)
        self.emit('call_tail', 0)
        self.emit('finish', 0xbc01)          # pop {r0}
        self.emit('return', 0x4700)          # bx r0
        self.labels['literal'] = self.pc
        struct.pack_into('<I', self.data, self.pc, BASE + 0x100)
        self.owner_size = self.pc + 4
        self.labels['veneer'] = 0x90
        self.patch('veneer', 0x4718)         # bx r3
        struct.pack_into('<H', self.data, 0x94, 0x4770)
        self.call_to(0x90)
        pc = self.labels['literal_load']
        delta = self.labels['literal'] - ((pc + 4) & ~3)
        self.patch('literal_load', 0x4900 | (delta // 4))  # ldr r1, [pc, #...]
        for pc, destination in self.fixups:
            self.branch_to(pc, self.labels[destination])
        self.functions = [dict(name='synthetic_owner', rom_offset=0,
                               size=self.owner_size, source='synthetic.c')]
        for index in range(16):
            if index < 4:
                offset = 0x200 + 8 * index
                mode = 'Thumb' if index % 2 == 0 else 'ARM'
                pointer = BASE + offset + (mode == 'Thumb')
                self.functions.append(dict(name='game_' + str(index),
                                           rom_offset=offset, size=4, mode=mode,
                                           source='game_' + str(index) + '.c'))
            else:
                pointer = 0x10000 + index * 0x1000 + (1 if index % 3 == 1
                                                    else 2 if index % 3 == 0 else 0)
            enabled = index in (0, 1, 3, 4, 6, 9, 11, 14)
            # A word read would incorrectly enable the deliberately disabled
            # cases. Only the low flag byte is part of the proven grammar.
            struct.pack_into('<II', self.data, 0x100 + 8 * index,
                             pointer, 0xa5000000 | (0x51 if enabled else 0))
        self.source_sha256 = digest(b'independent synthetic C owner')
        self.row = dict(proof_kind=OPERAND_PROOF_KIND, owner='synthetic_owner',
                        source_sha256=self.source_sha256,
                        rom_offset=self.labels['call'],
                        load_rom_offset=self.labels['load'],
                        literal_rom_offset=self.labels['literal'],
                        read_window_rom_offset=0x100,
                        read_window_sha256=digest(self.data[0x100:0x180]),
                        veneer_rom_offset=0x90)

    def emit(self, name, opcode):
        self.labels[name] = self.pc
        struct.pack_into('<H', self.data, self.pc, opcode)
        self.pc += 2

    def patch(self, name, opcode):
        struct.pack_into('<H', self.data, self.labels[name], opcode)

    def branch(self, name, destination):
        self.emit(name, 0)
        self.fixups.append((self.pc - 2, destination))

    def branch_to(self, pc, target, condition=0):
        delta = (target - pc - 4) // 2
        struct.pack_into('<H', self.data, pc,
                         0xd000 | (condition << 8) | (delta & 255))

    def call_to(self, target):
        pc = self.labels['call']
        delta = target - pc - 4
        struct.pack_into('<HH', self.data, pc,
                         0xf000 | ((delta >> 12) & 0x7ff),
                         0xf800 | ((delta >> 1) & 0x7ff))

    def pointer(self, index, value):
        struct.pack_into('<I', self.data, 0x100 + index * 8, value)
        self.rehash()

    def rehash(self):
        self.row['read_window_sha256'] = digest(self.data[0x100:0x180])

    def validate(self):
        return validate_saved_volume_operands(
            self.row, Scanner(bytes(self.data), []), self.functions,
            lambda owner: self.source_sha256)

    def call_record(self, kind='register_veneer_call'):
        return dict(site=BASE + self.labels['call'], kind=kind,
                    veneer_address=BASE + 0x90, targets_complete=False,
                    targets=[], limitation='existing callback uncertainty')


@unittest.skipUnless(HAS_CAPSTONE, 'Capstone is needed for native operand proof')
class BranchOperandDomainTests(unittest.TestCase):
    def test_quantifies_byte_and_actual_flag_without_table_or_runtime_credit(self):
        fixture = SavedByteFixture()
        result = fixture.validate()
        proof = result['bounded_branch_operands']
        self.assertTrue(proof['branch_operands_complete'])
        self.assertTrue(proof['game_direct_targets_owned'])
        self.assertEqual(proof['byte_inputs'], 256)
        self.assertEqual(proof['call_inputs'], 127)  # 15 + seven 16-value groups
        self.assertEqual(proof['game_call_inputs'], 47)
        self.assertEqual(proof['non_game_region00_call_inputs'], 80)
        self.assertEqual([v['owner'] for v in proof['game_targets']],
                         ['game_0', 'game_1', 'game_3'])
        self.assertEqual(len(proof['raw_operands']), 8)
        self.assertEqual(proof['read_window_bytes'], 128)
        self.assertNotIn('targets_complete', result)
        self.assertNotIn('kind', result)
        self.assertNotIn('table_rows', proof)
        # Metadata cannot promote an address-read span into a table declaration.
        fixture.row['read_window_bytes'] = 128
        self.assertEqual(fixture.validate(), result)

    def test_region00_words_are_retained_raw_including_thumb_and_unaligned_arm(self):
        fixture = SavedByteFixture()
        fixture.pointer(4, 0x00010203)  # odd raw word, not a normalized PC
        fixture.pointer(6, 0x00020402)  # ARM bit1 set: no alignment claim
        proof = fixture.validate()['bounded_branch_operands']
        self.assertIn(0x00010203, proof['non_game_region00_operands'])
        self.assertIn(0x00020402, proof['non_game_region00_operands'])
        self.assertNotIn('non_game_targets', proof)
        self.assertEqual(proof['game_call_inputs'], 47)

    def test_zero_saved_byte_and_zero_flag_skip_even_with_nonzero_flag_word(self):
        fixture = SavedByteFixture()
        # No target word is consumed when its flag byte is zero.
        fixture.pointer(2, 0x03000001)
        self.assertEqual(fixture.validate()['bounded_branch_operands']['call_inputs'], 127)
        for index in range(16):
            fixture.data[0x104 + 8 * index] = 0
        fixture.rehash()
        proof = fixture.validate()['bounded_branch_operands']
        self.assertEqual(proof['call_inputs'], 0)
        self.assertEqual(proof['raw_operands'], [])
        fixture.data[0x104] = 1
        fixture.rehash()
        self.assertEqual(fixture.validate()['bounded_branch_operands']['call_inputs'], 15)

    def test_read_window_and_source_pins_fail_independently(self):
        fixture = SavedByteFixture()
        fixture.data[0x17f] ^= 1  # last byte is pinned, although not a flag/word
        with self.assertRaisesRegex(ValueError, 'read-window pin'):
            fixture.validate()
        fixture = SavedByteFixture()
        fixture.row['source_sha256'] = '0' * 64
        with self.assertRaisesRegex(ValueError, 'source owner pin'):
            fixture.validate()

    def test_native_byte_arithmetic_flag_and_capture_drift_rejects(self):
        changes = [('field', 0x325c), ('load', 0x8810),  # LDRH
                   ('load', 0x6810),                   # LDR
                   ('narrow', 0x05c3), ('zero_test', 0x2800),
                   ('select', 0x0ed8), ('stride', 0x0082),
                   ('flag_address', 0x1cd3), ('flag_load', 0x5ac8),
                   ('flag_test', 0x2801), ('capture', 0x588a),
                   ('argument', 0x1c28), ('row_argument', 0x2101)]
        for name, opcode in changes:
            with self.subTest(instruction=name, opcode=opcode):
                fixture = SavedByteFixture()
                fixture.patch(name, opcode)
                with self.assertRaises(ValueError):
                    fixture.validate()

    def test_guards_cannot_invert_or_skip_to_another_successor(self):
        for name in ('zero_branch', 'flag_branch'):
            for condition, target in [(1, 'finish'), (0, 'capture')]:
                with self.subTest(guard=name, condition=condition, target=target):
                    fixture = SavedByteFixture()
                    fixture.branch_to(fixture.labels[name], fixture.labels[target], condition)
                    with self.assertRaises(ValueError):
                        fixture.validate()

    def test_extra_entry_edges_cannot_bypass_byte_capture_or_flag(self):
        for target in ('load', 'narrow', 'select', 'capture', 'call', 'call_tail'):
            with self.subTest(target=target):
                fixture = SavedByteFixture()
                fixture.branch_to(fixture.labels['entry_branch'], fixture.labels[target])
                with self.assertRaises(ValueError):
                    fixture.validate()

    def test_base_and_bx_register_must_be_the_proven_rom_capture(self):
        fixture = SavedByteFixture()
        struct.pack_into('<I', fixture.data, fixture.labels['literal'], 0x03000100)
        with self.assertRaisesRegex(ValueError, 'immutable ROM read window'):
            fixture.validate()
        fixture = SavedByteFixture()
        fixture.patch('veneer', 0x4720)  # BX R4 cannot consume captured R3
        with self.assertRaisesRegex(ValueError, 'veneer'):
            fixture.validate()
        fixture = SavedByteFixture()
        fixture.call_to(0x94)
        with self.assertRaises(ValueError):
            fixture.validate()

    def test_game_operands_require_exact_c_entry_mode_and_alignment(self):
        for pointer in (BASE + 0x280 + 1, BASE + 0x200, BASE + 0x20a):
            with self.subTest(pointer=pointer):
                fixture = SavedByteFixture()
                fixture.pointer(0, pointer)
                with self.assertRaises(ValueError):
                    fixture.validate()
        for change in ({'mode': 'ARM'}, {'kind': 'assembly_glue'},
                       {'ram_address': 0x03000200}):
            with self.subTest(owner=change):
                fixture = SavedByteFixture()
                fixture.functions[1].update(change)
                with self.assertRaisesRegex(ValueError, 'C source entry'):
                    fixture.validate()
        fixture = SavedByteFixture()
        fixture.functions.append(dict(fixture.functions[1]))
        with self.assertRaisesRegex(ValueError, 'C source entry'):
            fixture.validate()

    def test_cartridge_alias_is_game_and_cannot_escape_source_ownership(self):
        for window in (0x0a000000, 0x0c000000):
            with self.subTest(window=window):
                fixture = SavedByteFixture()
                fixture.pointer(0, window + 0x201)
                targets = fixture.validate()['bounded_branch_operands']['game_targets']
                alias = next(t for t in targets if t['raw'] == window + 0x201)
                self.assertEqual(alias['owner'], 'game_0')
                self.assertEqual(alias['address'], window + 0x200)
                fixture.functions = fixture.functions[:1]
                with self.assertRaisesRegex(ValueError, 'C source entry'):
                    fixture.validate()

    def test_ram_and_other_regions_reject_even_if_metadata_window_is_refreshed(self):
        for pointer in (0x01000001, 0x02000001, 0x03000001,
                        0x06000001, 0x07000001, 0x0e000001, 0xffffffff):
            with self.subTest(pointer=pointer):
                fixture = SavedByteFixture()
                fixture.pointer(4, pointer)
                with self.assertRaisesRegex(ValueError, 'unsupported address region'):
                    fixture.validate()

    def test_metadata_cannot_supply_targets_expand_window_or_change_entry(self):
        for key, value in [('raw_operands', []), ('targets_complete', True),
                           ('read_window_bytes', 127), ('read_window_bytes', True),
                           ('proof_kind', 'trust_me'), ('load_rom_offset', True),
                           ('read_window_rom_offset', -4),
                           ('read_window_rom_offset', 0x4fc),
                           ('rom_offset', 2), ('literal_rom_offset', 0x100)]:
            with self.subTest(key=key, value=value):
                fixture = SavedByteFixture()
                fixture.row[key] = value
                with self.assertRaises(ValueError):
                    fixture.validate()
        for change in ({'mode': 'ARM'}, {'kind': 'assembly_glue'},
                       {'ram_address': 0x03000000}):
            fixture = SavedByteFixture()
            fixture.functions[0].update(change)
            with self.assertRaisesRegex(ValueError, 'C ROM Thumb owner'):
                fixture.validate()

    def test_annotation_preserves_callback_fields_siblings_and_97_count(self):
        for kind in ('register_veneer_call', 'observed_table_call'):
            with self.subTest(kind=kind):
                fixture = SavedByteFixture()
                call = fixture.call_record(kind)
                siblings = [dict(site=BASE + 0x300 + i * 2,
                                 kind='register_veneer_call',
                                 veneer_address=BASE + 0x90,
                                 targets_complete=False, targets=[])
                            for i in range(96)]
                before = copy.deepcopy(call)
                siblings_before = copy.deepcopy(siblings)
                results = {'owner': {'transfer_records': [call] + siblings}}
                physical = lambda address: address - BASE
                self.assertEqual(len(unresolved_callback_sites([
                    {'transfer_records': [dict(r, rom_offset=physical(r['site']))
                                          for r in [call] + siblings]}])), 97)
                annotate_operand_records(results, physical, [fixture.validate()])
                self.assertTrue(call['bounded_branch_operands']['game_direct_targets_owned'])
                self.assertEqual({k: v for k, v in call.items()
                                  if k != 'bounded_branch_operands'}, before)
                self.assertEqual(siblings, siblings_before)
                rows = [{'transfer_records': [dict(r, rom_offset=physical(r['site']))
                                               for r in [call] + siblings]}]
                self.assertEqual(len(unresolved_callback_sites(rows)), 97)

    def test_annotation_rejects_duplicate_missing_wrong_and_already_attached(self):
        fixture = SavedByteFixture()
        proof = fixture.validate()
        with self.assertRaisesRegex(ValueError, 'duplicate'):
            annotate_operand_records({}, lambda a: a - BASE, [proof, proof])
        with self.assertRaisesRegex(ValueError, 'lacks a decoded call'):
            annotate_operand_records({}, lambda a: a - BASE, [proof])
        for key, value in [('kind', 'literal_transfer'),
                           ('veneer_address', BASE + 0x94),
                           ('bounded_branch_operands', {})]:
            with self.subTest(key=key):
                call = fixture.call_record()
                call[key] = value
                before = copy.deepcopy(call)
                with self.assertRaises(ValueError):
                    annotate_operand_records({'x': {'transfer_records': [call]}},
                                             lambda a: a - BASE, [proof])
                self.assertEqual(call, before)

    def test_copied_alias_and_late_validation_failure_are_atomic(self):
        fixture = SavedByteFixture()
        proof = fixture.validate()
        for failure in ('copied', 'wrong_veneer', 'missing_site'):
            with self.subTest(failure=failure):
                call = fixture.call_record()
                other = fixture.call_record()
                validated = [proof]
                if failure == 'copied':
                    other['site'] = 0x03000000 + fixture.labels['call']
                elif failure == 'wrong_veneer':
                    other['veneer_address'] += 4
                else:
                    other['site'] += 2
                    validated.append({**proof, 'rom_offset': proof['rom_offset'] + 4})
                results = {'rom': {'transfer_records': [call]},
                           'other': {'transfer_records': [other]}}
                before = copy.deepcopy(results)
                physical = lambda a: a - (BASE if a >= BASE else 0x03000000)
                with self.assertRaises(ValueError):
                    annotate_operand_records(results, physical, validated)
                self.assertEqual(results, before)


if __name__ == '__main__':
    unittest.main()
