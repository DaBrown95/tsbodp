"""Ensure source extents cannot overlap or hide unconverted bytes."""
import importlib.util
from pathlib import Path
import unittest

spec = importlib.util.spec_from_file_location('rom_layout', Path(__file__).resolve().parents[1] / 'tools/rom_layout.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


class LayoutTests(unittest.TestCase):
    def test_exact_partition_including_unconverted_gaps(self):
        regions = module.layout([{'name': 'f', 'rom_offset': 4, 'size': 8}], 20)
        self.assertEqual([(r['kind'], r['offset'], r['size']) for r in regions],
                         [('unconverted', 0, 4), ('compiled_c', 4, 8), ('unconverted', 12, 8)])

    def test_overlap_and_invalid_extents_rejected(self):
        for functions in ([{'name': 'a', 'rom_offset': 0, 'size': 8}, {'name': 'b', 'rom_offset': 4, 'size': 8}],
                          [{'name': 'a', 'rom_offset': -1, 'size': 4}],
                          [{'name': 'a', 'rom_offset': 0, 'size': 0}],
                          [{'name': 'a', 'rom_offset': 18, 'size': 4}],
                          [{'name': 'a', 'rom_offset': 0, 'size': 4}, {'name': 'a', 'rom_offset': 8, 'size': 4}]):
            with self.subTest(functions=functions), self.assertRaises(ValueError):
                module.layout(functions, 20)
