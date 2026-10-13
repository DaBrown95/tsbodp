"""A green tile requires current, complete matching-source evidence."""
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from render_progress import binary_layout, verify_functions, source_group


class ProgressTests(unittest.TestCase):
    def setUp(self):
        self.function = {'name': 'f', 'rom_offset': 4, 'size': 12}
        self.receipt = {**self.function, 'identical': True, 'source_reconstruction_verified': True,
                        'source_sha256': 'original', 'reference_size': 12, 'candidate_size': 12}

    def test_current_source_receipt_has_exact_credit(self):
        rows = verify_functions([self.function], [self.receipt], lambda f: 'original')
        self.assertEqual(rows[0]['status'], 'exact_c')

    def test_glue_cannot_receive_green_c_credit(self):
        glue = {**self.function, 'kind': 'assembly_glue'}
        with self.assertRaises(ValueError):
            verify_functions([glue], [self.receipt], lambda f: 'original')
        receipt = {**self.receipt, 'source_reconstruction_verified': False, 'assembly_glue_verified': True}
        rows = verify_functions([glue], [receipt], lambda f: 'original')
        self.assertEqual(rows[0]['status'], 'exact_glue')

    def test_changed_source_does_not_reuse_green_credit(self):
        with self.assertRaises(ValueError):
            verify_functions([self.function], [self.receipt], lambda f: 'changed')

    def test_inline_glue_requires_current_span_receipt_and_rejected_control(self):
        f = {**self.function, 'mode': 'ARM', 'inline_glue': {
            'source': 'include/bios.h', 'begin_prefix': '__tsbodp_glue_bios_begin_',
            'end_prefix': '__tsbodp_glue_bios_end_', 'spans': [{'offset': 4, 'size': 4}]}}
        r = {**self.receipt, 'inline_glue': f['inline_glue'], 'inline_glue_verified': True,
             'inline_glue_control': {'rejected': True}}
        rows = verify_functions([f], [r], lambda f: 'original')
        self.assertEqual([row['status'] for row in rows], ['exact_c', 'exact_glue', 'exact_c'])
        for change in ({'inline_glue': {}}, {'inline_glue_verified': False},
                       {'inline_glue_control': {'rejected': False}}):
            with self.subTest(change=change), self.assertRaises(ValueError):
                verify_functions([f], [{**r, **change}], lambda f: 'original')
        with self.assertRaisesRegex(ValueError, 'Stale inline glue coverage'):
            verify_functions([self.function], [r], lambda f: 'original')

    def test_binary_only_or_partial_match_rejected(self):
        for change in ({'source_reconstruction_verified': False}, {'identical': False},
                       {'candidate_size': 8}, {'size': 8}, {'rom_offset': 8}):
            with self.subTest(change=change), self.assertRaises(ValueError):
                verify_functions([self.function], [{**self.receipt, **change}], lambda f: 'original')

    def test_missing_or_duplicate_receipt_rejected(self):
        for receipts in ([], [self.receipt, self.receipt]):
            with self.assertRaises(ValueError):
                verify_functions([self.function], receipts, lambda f: 'original')

    def test_area_follows_actual_byte_weights(self):
        boxes = dict(binary_layout([('a', 2), ('b', 3), ('c', 5)], (0, 0, 100, 100)))
        self.assertEqual(sum(w*h for _, _, w, h in boxes.values()), 10000)
        for name, weight in [('a', 2), ('b', 3), ('c', 5)]:
            x, y, w, h = boxes[name]
            self.assertAlmostEqual(w*h, weight*1000)
            self.assertTrue(0 <= x < x+w <= 100 and 0 <= y < y+h <= 100)

    def test_copied_audio_and_split_glue_keep_the_verified_execution_group(self):
        rows = [{'rom_offset': 100, 'size': 48, 'group': 'ROM 08FDxxxx'}]
        for offset in (100, 108, 132):
            self.assertEqual(source_group({'rom_offset': offset, 'ram_copy': 'audio_iwram'}, rows),
                             'Copied audio / ARM')
        self.assertEqual(source_group({'rom_offset': 108}, rows), 'ROM 08FDxxxx')
        self.assertEqual(source_group({'rom_offset': 200}, rows), 'Verified source')

    def test_fake_zero_weight_tiles_rejected(self):
        with self.assertRaises(ValueError):
            binary_layout([('a', 0)], (0, 0, 100, 100))
