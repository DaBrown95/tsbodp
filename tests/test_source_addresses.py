"""Wrong copy mappings must fail before a source object is accepted."""
import copy
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from source_addresses import execution_address, validate_execution_layout, validate_symbol_definitions


class SourceAddressTests(unittest.TestCase):
    def setUp(self):
        self.copies = [{'name': 'code', 'rom_offset': 0x1000,
                        'ram_address': 0x03001000, 'size': 200}]
        self.function = {'rom_offset': 0x1020, 'size': 64, 'mode': 'ARM',
                         'ram_copy': 'code', 'ram_address': 0x03001020}

    def test_rom_source_and_copied_source_have_distinct_addresses(self):
        self.assertEqual(execution_address({'rom_offset': 0x1020, 'size': 64}), 0x08001020)
        self.assertEqual(execution_address(self.function, self.copies), 0x03001020)

    def test_wrong_destination_and_unknown_copy_are_rejected(self):
        for key, value in [('ram_address', 0x03001024), ('ram_copy', 'unknown')]:
            f = {**self.function, key: value}
            with self.subTest(key=key), self.assertRaises(ValueError):
                execution_address(f, self.copies)

    def test_extent_cannot_cross_copy_or_ram_end(self):
        with self.assertRaises(ValueError):
            execution_address({**self.function, 'size': 200}, self.copies)
        copies = [{**self.copies[0], 'ram_address': 0x03007FC0}]
        with self.assertRaises(ValueError):
            execution_address({**self.function, 'ram_address': 0x03007FE0}, copies)

    def test_mode_alignment_and_copy_pair_are_enforced(self):
        variants = [{**self.function, 'mode': 'invalid'},
                    {**self.function, 'ram_address': 0x03001022},
                    {**self.function, 'rom_offset': 0x1022}]
        f = copy.copy(self.function)
        del f['ram_address']
        variants.append(f)
        for f in variants:
            with self.subTest(function=f), self.assertRaises(ValueError):
                execution_address(f, self.copies)

    def test_overlapping_execution_extents_are_rejected(self):
        other = {**self.function, 'rom_offset': 0x1040, 'ram_address': 0x03001040}
        with self.assertRaises(ValueError):
            validate_execution_layout([self.function, other], self.copies)

    def test_observed_arm_entry_cannot_be_claimed_as_thumb(self):
        entries = [{'ram_address': 0x03001020, 'mode': 'ARM'}]
        with self.assertRaisesRegex(ValueError, 'instruction mode'):
            execution_address({**self.function, 'mode': 'Thumb'}, self.copies, entries)

    def test_external_alias_must_match_defined_rom_callee(self):
        definition = {'name': 'callee', 'rom_offset': 0x1000, 'size': 4}
        caller = {'name': 'caller', 'rom_offset': 0x2000, 'size': 4,
                  'symbols': {'callee': '0x08003001'}, 'thumb_symbols': ['callee']}
        with self.assertRaisesRegex(ValueError, 'callee.*execution address'):
            validate_symbol_definitions({'functions': [definition, caller]})
        for address, explicit in [('0x08001001', True), ('0x08001000', False)]:
            caller['symbols']['callee'] = address
            caller['thumb_symbols'] = ['callee'] if explicit else []
            validate_symbol_definitions({'functions': [definition, caller]})

    def test_copied_definition_alias_uses_ram_execution_address(self):
        definition = {**self.function, 'name': 'copied_callee'}
        caller = {'name': 'caller', 'rom_offset': 0x2000, 'size': 4,
                  'symbols': {'copied_callee': '0x08001020'}}
        with self.assertRaisesRegex(ValueError, 'execution address'):
            validate_symbol_definitions({'functions': [definition, caller]}, self.copies)
        caller['symbols']['copied_callee'] = '0x03001020'
        validate_symbol_definitions({'functions': [definition, caller]}, self.copies)

    def test_alias_mode_is_checked_against_c_and_glue_definitions(self):
        caller = {'name': 'caller', 'rom_offset': 0x2000, 'size': 4,
                  'symbols': {'callee': '0x08001001'}, 'thumb_symbols': ['callee']}
        definition = {'name': 'callee', 'rom_offset': 0x1000, 'size': 4,
                      'kind': 'assembly_glue', 'mode': 'ARM'}
        with self.assertRaisesRegex(ValueError, 'ARM definition'):
            validate_symbol_definitions({'functions': [caller], 'assembly': [definition]})
        caller['thumb_symbols'] = []
        with self.assertRaisesRegex(ValueError, 'execution address'):
            validate_symbol_definitions({'functions': [caller], 'assembly': [definition]})
        caller['symbols']['callee'] = '0x08001000'
        validate_symbol_definitions({'functions': [caller], 'assembly': [definition]})
        definition['mode'] = 'Thumb'
        caller['thumb_symbols'] = ['callee']
        with self.assertRaisesRegex(ValueError, 'mode bit'):
            validate_symbol_definitions({'functions': [caller], 'assembly': [definition]})

    def test_unconverted_alias_and_nondefining_storage_remain_explicit(self):
        definition = {'name': 'unconverted_entry', 'rom_offset': 0x1000, 'size': 4,
                      'defines_symbol': False}
        caller = {'name': 'caller', 'rom_offset': 0x2000, 'size': 4,
                  'symbols': {'unconverted_entry': '0x03001020', 'original': '0x08004001'}}
        validate_symbol_definitions({'functions': [definition, caller]})

    def test_duplicate_definition_rejects_before_symbol_resolution(self):
        function = {'name': 'callee', 'rom_offset': 0x1000, 'size': 4}
        with self.assertRaisesRegex(ValueError, 'Duplicate'):
            validate_symbol_definitions({'functions': [function, function]})
