"""Inventory uncertainty and byte accounting survive false-code controls."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from inventory_partition import partition, overlay, verify_discovery
try:
    from inventory_rom import Scanner, BASE
except ModuleNotFoundError:
    Scanner = None


class AccountingTests(unittest.TestCase):
    def test_all_bytes_including_gaps_accounted_once(self):
        rows = [{'name': 'code', 'rom_offset': 4, 'size': 3, 'status': 'candidate'}]
        parts = partition(rows, 10)
        self.assertEqual([(p['rom_offset'], p['size']) for p in parts], [(0, 4), (4, 3), (7, 3)])
        self.assertEqual(sum(p['size'] for p in parts), 10)
        self.assertNotIn('exact_c', [p['status'] for p in parts])

    def test_overlapping_or_out_of_rom_ranges_rejected(self):
        row = {'name': 'a', 'rom_offset': 4, 'size': 4, 'status': 'candidate'}
        for rows in ([row, row], [{**row, 'size': 7}], [{**row, 'size': 0}]):
            with self.assertRaises(ValueError):
                partition(rows, 10)

    def test_verified_overlay_preserves_every_unconverted_remainder(self):
        rows = [{'name': 'estimate', 'rom_offset': 0, 'size': 20, 'status': 'candidate'}]
        exact = [{'name': 'source', 'rom_offset': 4, 'size': 8, 'status': 'exact_c'}]
        parts = partition(overlay(rows, exact), 20)
        self.assertEqual([(p['size'], p['status']) for p in parts], [(4, 'candidate'), (8, 'exact_c'), (8, 'candidate')])

    def test_scanner_cannot_forge_green_tiles(self):
        rows = [{'name': 'fake', 'rom_offset': 0, 'size': 10, 'status': 'exact_c'}]
        data = {'reference_sha256': 'ref', 'rom_bytes': 10,
                'complete_rom_partition': True, 'complete_code_inventory': False,
                'entry_count': 1, 'mapped_extent_bytes': 10,
                'rows': rows, 'partition': partition(rows, 10)}
        with self.assertRaises(ValueError):
            verify_discovery(data, 10, 'ref')


@unittest.skipIf(Scanner is None, 'Capstone is needed for scanner controls')
class ScannerTests(unittest.TestCase):
    def scanner(self, hex_bytes, evidence='startup'):
        scanner = Scanner(bytes.fromhex(hex_bytes), [])
        scanner.seed(BASE, 'Thumb', evidence)
        scanner.drain()
        return scanner

    def test_conditional_branch_is_not_a_call(self):
        # blo +0; both arms return. A mnemonic-prefix test mistakes blo for bl.
        scanner = self.scanner('00d370477047')
        self.assertEqual(len(scanner.entries), 1)
        self.assertEqual(scanner.results[(BASE, 'Thumb')]['calls'], set())

    def test_ge_branch_keeps_both_paths(self):
        scanner = self.scanner('00da70477047')
        self.assertEqual(set(scanner.results[(BASE, 'Thumb')]['instructions']), {BASE, BASE+2, BASE+4})

    def test_literal_pool_is_not_disassembled(self):
        scanner = self.scanner('0048704700b50000')
        result = scanner.results[(BASE, 'Thumb')]
        self.assertEqual(set(result['instructions']), {BASE, BASE+2})
        self.assertEqual(result['literals'], {4, 5, 6, 7})

    def test_candidate_call_cannot_promote_itself_to_grounded_code(self):
        scanner = self.scanner('00f002f8704700007047', 'prologue candidate')
        evidence = scanner.entries[(BASE+8, 'Thumb')]['evidence']
        self.assertEqual(evidence, {'candidate call'})

    def test_thumb2_encoding_rejected_on_arm7(self):
        scanner = self.scanner('00bf7047')
        result = scanner.results[(BASE, 'Thumb')]
        self.assertEqual(result['instructions'], {})
        self.assertIn('non-ARM7 instruction', result['issues'])

    def test_ram_alias_uses_original_rom_offset(self):
        scanner = Scanner(bytes.fromhex('000000007047'), [
            {'ram_address': 0x03000000, 'rom_offset': 4, 'size': 2}])
        self.assertEqual(scanner.physical(0x03000000), 4)
        self.assertEqual(scanner.physical(BASE+4), 4)

    def test_pop_then_bx_is_return_not_unknown_callback(self):
        scanner = self.scanner('02bc0847')
        self.assertEqual(scanner.results[(BASE, 'Thumb')]['unresolved_transfers'], set())
