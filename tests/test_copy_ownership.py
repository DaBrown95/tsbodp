"""Copied tails and overlapping installations must not manufacture source credit."""
from copy import deepcopy
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from copy_ownership import project_copy_ownership
from source_coverage import coverage_rows


class CopyOwnershipTests(unittest.TestCase):
    def setUp(self):
        self.sources = [
            {'name': 'first', 'source': 'src/first.c', 'rom_offset': 8,
             'size': 16, 'status': 'exact_c'},
            {'name': 'next', 'source': 'src/next.c', 'rom_offset': 24,
             'size': 12, 'status': 'exact_c'},
            {'name': 'glue', 'source': 'src/glue.s', 'rom_offset': 40,
             'size': 4, 'status': 'exact_glue'}]

    def copy(self, name, start, size, address=0x03000000):
        return {'name': name, 'rom_offset': start, 'size': size, 'ram_address': address}

    def project(self, copies, sources=None):
        return project_copy_ownership(copies, self.sources if sources is None else sources, 64)

    def test_following_prefix_has_existing_owner_without_claiming_function_at_alias(self):
        result = self.project([self.copy('copy', 8, 20)])
        first, tail = result['installations'][0]['segments']
        self.assertTrue(first['whole_source_extent'])
        self.assertEqual((tail['source_extent_name'], tail['size'], tail['ram_address']),
                         ('next', 4, 0x03000010))
        self.assertFalse(tail['whole_source_extent'])
        self.assertEqual(result['unique_rom_counts']['compiled_c'], 20)

    def test_overlapping_installations_count_physical_bytes_once(self):
        result = self.project([self.copy('one', 8, 20), self.copy('two', 24, 12, 0x03001000)])
        self.assertEqual((result['installation_bytes'], result['unique_rom_bytes'],
                          result['duplicate_installation_bytes']), (32, 28, 4))
        self.assertEqual(result['unique_rom_counts']['compiled_c'], 28)

    def test_gaps_and_glue_are_separate_from_compiled_c(self):
        result = self.project([self.copy('mixed', 4, 44)])
        self.assertEqual(result['unique_rom_counts'],
                         {'compiled_c': 28, 'assembly_glue': 4, 'without_verified_source': 12})
        self.assertEqual(sum(s['size'] for s in result['installations'][0]['segments']), 44)

    def test_whole_copy_without_source_does_not_become_code(self):
        result = self.project([self.copy('data_or_unknown', 48, 8)])
        self.assertEqual(result['unique_rom_counts']['without_verified_source'], 8)
        self.assertEqual(result['unique_rom_counts']['compiled_c'], 0)

    def test_inline_hardware_glue_remains_separately_counted(self):
        function = {'name': 'with_glue', 'source': 'src/with_glue.c',
                    'rom_offset': 0, 'size': 16, 'status': 'exact_c',
                    'inline_glue': {'source': 'include/irq.h',
                                    'begin_prefix': '__tsbodp_glue_begin_',
                                    'end_prefix': '__tsbodp_glue_end_',
                                    'spans': [{'offset': 4, 'size': 4}]}}
        result = self.project([self.copy('one', 0, 16), self.copy('two', 4, 8)],
                              coverage_rows(function))
        self.assertEqual(result['unique_rom_counts'],
                         {'compiled_c': 12, 'assembly_glue': 4, 'without_verified_source': 0})

    def test_unverified_or_overlapping_source_claim_rejected(self):
        for change in ({'status': 'mapped_code'}, {'rom_offset': 16}, {'source': ''}):
            sources = deepcopy(self.sources)
            sources[1].update(change)
            with self.subTest(change=change), self.assertRaises(ValueError):
                self.project([self.copy('copy', 8, 20)], sources)

    def test_invalid_copy_extent_address_or_duplicate_name_rejected(self):
        for copies in ([self.copy('bad', -1, 4)], [self.copy('bad', 60, 8)],
                       [self.copy('bad', 4, 0)], [self.copy('bad', 4, 4, -1)],
                       [self.copy('bad', 4, 4, 0xffffffff)],
                       [self.copy('same', 4, 4), self.copy('same', 8, 4)]):
            with self.subTest(copies=copies), self.assertRaises(ValueError):
                self.project(copies)

    def test_inputs_are_unchanged(self):
        copies = [self.copy('copy', 8, 20)]
        old = deepcopy((copies, self.sources))
        self.project(copies)
        self.assertEqual((copies, self.sources), old)


if __name__ == '__main__':
    unittest.main()
