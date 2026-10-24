"""A guarded byte dispatch must fail closed when its native premises change.

Fixtures below assemble a small synthetic Thumb program, not a game function.
Its two input paths, distant dispatch block and independent table exercise the
proof across control flow, register provenance and immutable target capture.
"""
import hashlib
import importlib.util
import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))

HAS_CAPSTONE = importlib.util.find_spec('capstone') is not None
if HAS_CAPSTONE:
    from bounded_indirect import (BASE, PROOF_KIND, validate_bounded_table,
                                  annotate_bounded_records)
    from inventory_rom import Scanner


def digest(data):
    return hashlib.sha256(data).hexdigest()


class ThumbFixture:
    """Minimal labelled encoder for independently authored test instructions."""
    def __init__(self, input_call=False):
        self.data = bytearray(0x300)
        self.labels, self.fixups = {}, []
        self.pc = 0
        self.emit('entry', 0xb500)             # push {lr}
        self.emit('input_test', 0x2800)        # cmp r0, #0
        self.branch('input_branch', 'byte_load', 0)  # beq
        self.emit('zero', 0x2400)              # movs r4, #0
        self.branch('zero_to_guard', 'guard')
        self.emit('byte_load', 0x781c)         # ldrb r4, [r3]
        if input_call:
            self.call('input_call', 0x84)
        self.emit('guard', 0x2c60)             # cmp r4, #96
        self.branch('guard_branch', 'skip', 9) # bls
        self.branch('to_dispatch', 'dispatch')
        self.emit('skip', 0xbc01)              # pop {r0}
        self.emit('skip_return', 0x4700)        # bx r0
        self.pc = 0x30
        self.emit('dispatch', 0x1c21)          # adds r1, r4, #0
        self.emit('subtract', 0x3960)          # subs r1, #96
        self.emit('narrow', 0x060c)            # lsls r4, r1, #24
        self.emit('track_address', 0x1c2b)     # adds r3, r5, #0
        self.literal_load('table_load', 'literal', 0)
        self.emit('select', 0x0f22)            # lsrs r2, r4, #28
        self.emit('field_address', 0x335d)     # adds r3, #93
        self.emit('track_store', 0x7019)       # strb r1, [r3]
        self.emit('stride', 0x00d1)            # lsls r1, r2, #3
        self.emit('target_load', 0x5844)       # ldr r4, [r0, r1]
        self.emit('argument', 0x1c28)          # adds r0, r5, #0
        self.emit('row_argument', 0x2101)      # movs r1, #1
        self.call('call', 0x80)
        self.emit('pop_return', 0xbc01)
        self.emit('return', 0x4700)
        self.labels['literal'] = self.pc
        struct.pack_into('<I', self.data, self.pc, BASE + 0x100)
        self.owner_size = self.pc + 4
        self.labels['veneer'] = 0x80
        struct.pack_into('<HH', self.data, 0x80, 0x4720, 0x4770)
        struct.pack_into('<H', self.data, 0x84, 0x4770)
        self.functions = [dict(name='synthetic_owner', rom_offset=0,
                               size=self.owner_size, source='synthetic.c')]
        for index in range(10):
            offset = 0x200 + index * 4
            struct.pack_into('<H', self.data, offset, 0x4770)
            struct.pack_into('<II', self.data, 0x100 + index * 8,
                             BASE + offset + 1, 0xdead0000 + index)
            self.functions.append(dict(name='target_' + str(index),
                                       rom_offset=offset, size=2,
                                       source='target_' + str(index) + '.c'))
        self.resolve()
        self.source_sha256 = digest(b'synthetic source')
        self.row = dict(proof_kind=PROOF_KIND, owner='synthetic_owner',
                        source_sha256=self.source_sha256,
                        rom_offset=self.labels['call'],
                        guard_rom_offset=self.labels['guard'],
                        dispatch_rom_offset=self.labels['dispatch'],
                        literal_rom_offset=self.labels['literal'],
                        table_rom_offset=0x100, table_rows=10, record_stride=8,
                        table_sha256=digest(self.data[0x100:0x150]),
                        veneer_rom_offset=0x80)

    def emit(self, label, instruction):
        self.labels[label] = self.pc
        struct.pack_into('<H', self.data, self.pc, instruction)
        self.pc += 2

    def branch(self, label, destination, condition=None):
        self.emit(label, 0)
        self.fixups.append(('branch', self.pc - 2, destination, condition))

    def call(self, label, destination):
        self.emit(label, 0)
        self.emit(label + '_tail', 0)
        self.fixups.append(('call', self.pc - 4, destination, None))

    def literal_load(self, label, destination, register):
        self.emit(label, 0)
        self.fixups.append(('literal', self.pc - 2, destination, register))

    def resolve(self):
        for kind, pc, target, extra in self.fixups:
            target = self.labels[target] if isinstance(target, str) else target
            if kind == 'branch':
                self.patch_branch(pc, target, extra)
            elif kind == 'call':
                delta = target - pc - 4
                struct.pack_into('<HH', self.data, pc,
                                 0xf000 | ((delta >> 12) & 0x7ff),
                                 0xf800 | ((delta >> 1) & 0x7ff))
            else:
                delta = target - ((pc + 4) & ~3)
                assert delta >= 0 and delta % 4 == 0
                struct.pack_into('<H', self.data, pc,
                                 0x4800 | (extra << 8) | (delta // 4))

    def patch_branch(self, pc, target, condition=None):
        delta = (target - pc - 4) // 2
        opcode = (0xe000 | (delta & 0x7ff)) if condition is None else (
            0xd000 | (condition << 8) | (delta & 255))
        struct.pack_into('<H', self.data, pc, opcode)

    def patch(self, label, instruction):
        struct.pack_into('<H', self.data, self.labels[label], instruction)

    def rehash_table(self):
        self.row['table_sha256'] = digest(self.data[0x100:0x150])

    def validate(self):
        return validate_bounded_table(self.row, Scanner(bytes(self.data), []),
                                      self.functions, lambda owner: self.source_sha256)


@unittest.skipUnless(HAS_CAPSTONE, 'Capstone is needed for native selector proof')
class BoundedIndirectTests(unittest.TestCase):
    def test_guarded_byte_closes_only_the_actual_callback_column(self):
        fixture = ThumbFixture()
        result = fixture.validate()
        self.assertEqual(result['targets'], [BASE + 0x200 + i * 4 for i in range(10)])
        self.assertTrue(result['targets_complete'])
        self.assertEqual(result['selector_bounds'], [0, 9])
        self.assertEqual(result['bounded_selector_proof']['dispatch_inputs'], 159)
        self.assertEqual(result['bounded_selector_proof']['byte_definition_rom_offsets'],
                         [fixture.labels['zero'], fixture.labels['byte_load']])
        # The second words have deliberately non-pointer values; changing them
        # and the corresponding data pin cannot change this call's target set.
        for i in range(10):
            struct.pack_into('<I', fixture.data, 0x104 + i * 8, 0xffffffff)
        fixture.rehash_table()
        self.assertEqual(fixture.validate()['targets'], result['targets'])

    def test_unguarded_dispatch_and_mid_guard_entries_are_rejected(self):
        for destination in ('dispatch', 'guard_branch', 'to_dispatch', 'target_load'):
            with self.subTest(destination=destination):
                fixture = ThumbFixture()
                fixture.patch_branch(fixture.labels['input_branch'],
                                     fixture.labels[destination], 0)
                with self.assertRaises(ValueError):
                    fixture.validate()

    def test_byte_provenance_requires_every_entry_path(self):
        fixture = ThumbFixture()
        fixture.patch('zero', 0x46c0)  # real no-op leaves incoming R4 unbounded
        with self.assertRaisesRegex(ValueError, 'definition-free'):
            fixture.validate()
        fixture = ThumbFixture()
        fixture.patch('byte_load', 0x881c)  # LDRH can supply values above255
        with self.assertRaisesRegex(ValueError, 'non-byte definition'):
            fixture.validate()

    def test_call_between_definition_and_guard_is_not_assumed_harmless(self):
        with self.assertRaisesRegex(ValueError, 'call intervenes'):
            ThumbFixture(input_call=True).validate()

    def test_guard_arithmetic_and_actual_capture_cannot_drift(self):
        changes = [('guard', 0x2c5f), ('guard_branch', 0xd800),
                   ('subtract', 0x395f), ('narrow', 0x05cc),
                   ('select', 0x0ee2), ('stride', 0x0091),
                   ('target_load', 0x5884), ('track_store', 0x781c)]
        for label, opcode in changes:
            with self.subTest(label=label):
                fixture = ThumbFixture()
                fixture.patch(label, opcode)
                with self.assertRaises(ValueError):
                    fixture.validate()

    def test_literal_and_table_pins_are_independent_of_mode_and_entry_checks(self):
        fixture = ThumbFixture()
        struct.pack_into('<I', fixture.data, fixture.labels['literal'], 0x03000100)
        with self.assertRaisesRegex(ValueError, 'immutable ROM table'):
            fixture.validate()
        fixture = ThumbFixture()
        fixture.data[0x100] ^= 4
        with self.assertRaisesRegex(ValueError, 'table prefix pin'):
            fixture.validate()
        for pointer in (0, 0x03000001, BASE + 0x200, BASE + 0x203):
            with self.subTest(pointer=pointer):
                fixture = ThumbFixture()
                struct.pack_into('<I', fixture.data, 0x100, pointer)
                fixture.rehash_table()
                with self.assertRaises(ValueError):
                    fixture.validate()
        fixture = ThumbFixture()
        fixture.functions[1]['mode'] = 'ARM'
        with self.assertRaisesRegex(ValueError, 'source entry'):
            fixture.validate()

    def test_wrong_veneer_or_stale_source_cannot_close_the_call(self):
        fixture = ThumbFixture()
        fixture.patch('veneer', 0x4718)  # BX R3, not the captured R4 target
        with self.assertRaisesRegex(ValueError, 'veneer'):
            fixture.validate()
        fixture = ThumbFixture()
        fixture.row['source_sha256'] = '0' * 64
        with self.assertRaisesRegex(ValueError, 'source owner pin'):
            fixture.validate()

    def test_metadata_cannot_expand_supported_layout_or_change_owner_mode(self):
        for key, value in [('proof_kind', 'trust_me'), ('table_rows', 16),
                           ('record_stride', 4), ('rom_offset', True),
                           ('literal_rom_offset', 0x100), ('table_rom_offset', -4)]:
            with self.subTest(key=key):
                fixture = ThumbFixture()
                fixture.row[key] = value
                with self.assertRaises(ValueError):
                    fixture.validate()
        fixture = ThumbFixture()
        fixture.functions[0]['mode'] = 'ARM'
        with self.assertRaisesRegex(ValueError, 'ROM Thumb owner'):
            fixture.validate()

    def test_unsupported_or_overlapping_control_flow_rejects(self):
        fixture = ThumbFixture()
        fixture.patch('zero', 0x4718)  # BX R3 is not a saved-return sequence
        with self.assertRaisesRegex(ValueError, 'register transfer'):
            fixture.validate()
        fixture = ThumbFixture()
        fixture.patch_branch(fixture.labels['input_branch'],
                             fixture.labels['call_tail'], 0)
        with self.assertRaises(ValueError):
            fixture.validate()

    def test_annotation_requires_the_decoded_call_and_preserves_other_consumers(self):
        fixture = ThumbFixture()
        bounded = fixture.validate()
        call = dict(site=BASE + fixture.labels['call'], kind='register_veneer_call',
                    veneer_address=BASE + 0x80, targets_complete=False, targets=[])
        other = dict(site=BASE + 0x90, kind='register_veneer_call',
                     veneer_address=BASE + 0x80, targets_complete=False, targets=[])
        results = {'owner': {'transfer_records': [call, other]}}
        physical = lambda address: address - BASE
        annotate_bounded_records(results, physical, [bounded])
        self.assertEqual(call['site'], BASE + fixture.labels['call'])
        self.assertEqual(call['kind'], 'bounded_table_call')
        self.assertTrue(call['targets_complete'])
        self.assertFalse(other['targets_complete'])
        with self.assertRaises(ValueError):
            annotate_bounded_records({}, physical, [bounded])
        with self.assertRaises(ValueError):
            annotate_bounded_records(results, physical, [bounded, bounded])
        call['veneer_address'] += 4
        with self.assertRaises(ValueError):
            annotate_bounded_records(results, physical, [bounded])

    def test_rom_proof_cannot_silently_close_a_copied_alias(self):
        fixture = ThumbFixture()
        bounded = fixture.validate()
        call = dict(site=BASE + fixture.labels['call'], kind='register_veneer_call',
                    veneer_address=BASE + 0x80, targets_complete=False, targets=[])
        alias = {**call, 'site': 0x03000000 + fixture.labels['call']}
        results = {'rom': {'transfer_records': [call]},
                   'copy': {'transfer_records': [alias]}}
        physical = lambda address: address - (BASE if address >= BASE else 0x03000000)
        with self.assertRaisesRegex(ValueError, 'copied call alias'):
            annotate_bounded_records(results, physical, [bounded])
        self.assertFalse(call['targets_complete'])
        self.assertFalse(alias['targets_complete'])


if __name__ == '__main__':
    unittest.main()
