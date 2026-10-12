"""A stale or no-op mutation must not masquerade as a negative control."""
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from source_controls import mutate


class ControlTests(unittest.TestCase):
    def test_actual_source_change(self):
        self.assertEqual(mutate('mask = 1;', {'before': 'mask = 1;', 'after': 'mask = 2;'}), 'mask = 2;')

    def test_stale_empty_and_no_op_controls_rejected(self):
        for control in ({'before': 'old', 'after': 'new'}, {'before': '', 'after': 'new'},
                        {'before': 'mask', 'after': 'mask'}):
            with self.subTest(control=control), self.assertRaises(ValueError):
                mutate('mask = 1;', control)
