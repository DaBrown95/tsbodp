"""A new callback must retain its declared Thumb mode without classifying data."""
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from source_symbols import declarations


class SymbolTests(unittest.TestCase):
    def test_callback_mode_is_explicit(self):
        lines = declarations({'callback': '0x08001235', 'odd_data': '0x03000001'}, ['callback'])
        self.assertIn('.thumb_set callback, 0x08001235', lines)
        self.assertIn('.set odd_data, 0x03000001', lines)

    def test_missing_address_and_missing_mode_bit_rejected(self):
        for symbols, functions in [({}, ['callback']), ({'callback': '0x08001234'}, ['callback'])]:
            with self.subTest(symbols=symbols), self.assertRaises(ValueError):
                declarations(symbols, functions)
