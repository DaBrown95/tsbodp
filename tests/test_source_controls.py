"""A stale or no-op mutation must not masquerade as a negative control."""
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from source_controls import mutate, require_negative_controls, verified_comparison


class ControlTests(unittest.TestCase):
    def test_missing_control_blocks_manifest(self):
        with self.assertRaisesRegex(ValueError, 'uncontrolled'):
            require_negative_controls([{'name': 'uncontrolled'}])

    def test_bad_control_metadata_is_rejected(self):
        for control in (None, {}, {'before': 1, 'after': '2'},
                        {'before': 'old', 'after': None},
                        {'before': 'same', 'after': 'same'}):
            with self.subTest(control=control), self.assertRaises(ValueError):
                require_negative_controls([{'name': 'bad', 'negative_control': control}])
        with self.assertRaisesRegex(ValueError, 'inline'):
            require_negative_controls([{'name': 'inline',
                                        'negative_control': {'before': 'old', 'after': 'new'},
                                        'inline_glue': {'source': 'glue.h'}}])

    def test_positive_only_comparison_is_not_verified(self):
        self.assertFalse(verified_comparison({'identical': True}))
        self.assertFalse(verified_comparison({'identical': True,
                                             'negative_control': {'before': 'old', 'after': 'new'}}))

    def test_rejection_flag_cannot_hide_matching_control(self):
        self.assertFalse(verified_comparison({'identical': True,
                                             'negative_control': {'identical': True, 'rejected': True}},
                                            controls_compiled=True))
        self.assertFalse(verified_comparison({'identical': False,
                                             'negative_control': {'identical': False, 'rejected': True}},
                                            controls_compiled=True))

    def test_result_like_metadata_cannot_verify_uncompiled_controls(self):
        function = {'name': 'metadata',
                    'negative_control': {'before': 'old', 'after': 'new',
                                         'identical': False, 'rejected': True}}
        require_negative_controls([function])
        result = {'identical': True, **function}
        self.assertFalse(verified_comparison(result))
        self.assertFalse(verified_comparison(result, controls_compiled=False))

    def test_body_control_does_not_verify_inline_glue(self):
        self.assertFalse(verified_comparison({'identical': True,
                                             'negative_control': {'identical': False, 'rejected': True},
                                             'inline_glue': {'source': 'glue.h'}},
                                            controls_compiled=True))

    def test_rejected_body_and_inline_controls_verify(self):
        control = {'identical': False, 'rejected': True}
        result = {'identical': True, 'negative_control': control}
        self.assertTrue(verified_comparison(result, controls_compiled=True))
        result.update({'inline_glue': {'source': 'glue.h'}, 'inline_glue_control': control})
        self.assertTrue(verified_comparison(result, controls_compiled=True))

    def test_actual_source_change(self):
        self.assertEqual(mutate('mask = 1;', {'before': 'mask = 1;', 'after': 'mask = 2;'}), 'mask = 2;')

    def test_stale_empty_and_no_op_controls_rejected(self):
        for control in ({'before': 'old', 'after': 'new'}, {'before': '', 'after': 'new'},
                        {'before': 'mask', 'after': 'mask'}):
            with self.subTest(control=control), self.assertRaises(ValueError):
                mutate('mask = 1;', control)
