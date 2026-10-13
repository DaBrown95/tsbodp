"""Hardware assembly must not silently receive C coverage."""
import copy
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from source_coverage import byte_counts, coverage_rows, inline_glue, verify_inline_glue_symbols


class InlineGlueTests(unittest.TestCase):
    def setUp(self):
        self.function = {'name': 'mixer', 'size': 48, 'rom_offset': 100, 'mode': 'ARM',
                         'inline_glue': {'source': 'include/bios.h',
                                         'begin_prefix': '__tsbodp_glue_bios_begin_',
                                         'end_prefix': '__tsbodp_glue_bios_end_',
                                         'spans': [{'offset': 8, 'size': 8}, {'offset': 24, 'size': 8}]}}
        self.symbols = {'__tsbodp_glue_bios_begin_1': 0x3000008,
                        '__tsbodp_glue_bios_end_1': 0x3000010,
                        '__tsbodp_glue_bios_begin_3': 0x3000018,
                        '__tsbodp_glue_bios_end_3': 0x3000020}

    def test_linked_markers_prove_the_spans_and_split_credit(self):
        verify_inline_glue_symbols(self.function, self.symbols, 0x3000000)
        self.assertEqual(byte_counts(self.function), (32, 16))
        rows = coverage_rows({**self.function, 'status': 'exact_c'})
        self.assertEqual([(r['rom_offset'], r['size'], r['status']) for r in rows],
                         [(100, 8, 'exact_c'), (108, 8, 'exact_glue'),
                          (116, 8, 'exact_c'), (124, 8, 'exact_glue'), (132, 16, 'exact_c')])

    def test_overlap_outside_extent_alignment_and_zero_size_are_rejected(self):
        for spans in ([{'offset': 8, 'size': 16}, {'offset': 20, 'size': 8}],
                      [{'offset': 44, 'size': 8}], [{'offset': 9, 'size': 8}],
                      [{'offset': 8, 'size': 0}], [{'offset': 0, 'size': 48}], []):
            f = copy.deepcopy(self.function)
            f['inline_glue']['spans'] = spans
            with self.subTest(spans=spans), self.assertRaises(ValueError):
                inline_glue(f)

    def test_removed_declaration_cannot_turn_glue_into_c_credit(self):
        f = {k: v for k, v in self.function.items() if k != 'inline_glue'}
        with self.assertRaisesRegex(ValueError, 'missing its coverage'):
            verify_inline_glue_symbols(f, self.symbols, 0x3000000)

    def test_shifted_missing_or_unclaimed_compiled_markers_rejected(self):
        for change in ('shift', 'missing', 'extra', 'suffix'):
            symbols = dict(self.symbols)
            if change == 'shift':
                symbols['__tsbodp_glue_bios_begin_1'] += 4
            elif change == 'missing':
                del symbols['__tsbodp_glue_bios_end_1']
            elif change == 'extra':
                symbols['__tsbodp_glue_other_2'] = 0x3000014
            else:
                symbols['__tsbodp_glue_bios_begin_bad'] = 0x3000014
            with self.subTest(change=change), self.assertRaises(ValueError):
                verify_inline_glue_symbols(self.function, symbols, 0x3000000)

    def test_changed_coverage_without_changed_source_is_rejected(self):
        f = copy.deepcopy(self.function)
        f['inline_glue']['spans'][0]['size'] = 4
        with self.assertRaisesRegex(ValueError, 'differ from declared'):
            verify_inline_glue_symbols(f, self.symbols, 0x3000000)

    def test_header_traversal_and_overlapping_marker_names_rejected(self):
        for change in ({'source': 'include/../private.h'},
                       {'end_prefix': '__tsbodp_glue_bios_begin_end_'}):
            f = copy.deepcopy(self.function)
            f['inline_glue'].update(change)
            with self.subTest(change=change), self.assertRaises(ValueError):
                inline_glue(f)

    def test_separate_assembly_extent_never_receives_c_bytes(self):
        self.assertEqual(byte_counts({'kind': 'assembly_glue', 'size': 28}), (0, 28))
        f = copy.deepcopy(self.function)
        f['kind'] = 'assembly_glue'
        with self.assertRaises(ValueError):
            byte_counts(f)
