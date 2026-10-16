"""Inventory uncertainty and byte accounting survive false-code controls."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from inventory_partition import partition, overlay, verify_discovery
try:
    from inventory_rom import (Scanner, BASE, unresolved_callback_sites,
                               observed_extent_counts, finalize_extent_observations)
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

    def test_compiler_extent_replaces_prior_bounded_map_once(self):
        old = {'name': 'VBlank wrapper', 'rom_offset': 4, 'size': 8, 'status': 'mapped_code'}
        source = {**old, 'name': 'irq_vblank'}
        rows = overlay([old], [source])
        self.assertEqual(rows, [source])
        self.assertEqual(sum(r['size'] for r in partition(rows, 16)), 16)

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
    def test_verified_extent_recovers_pool_beyond_prior_entry_clip(self):
        observed = {'instruction_offsets': set(range(100, 106)),
                    'literal_offsets': set(range(108, 112)) | set(range(116, 120))}
        before = {key: set(value) for key, value in observed.items()}
        self.assertEqual(observed_extent_counts(observed, 100, 12),
                         {'decoded_instruction_bytes': 6, 'referenced_literal_bytes': 4})
        self.assertEqual(observed_extent_counts(observed, 100, 20),
                         {'decoded_instruction_bytes': 6, 'referenced_literal_bytes': 8})
        self.assertEqual(observed, before)

    def test_replacement_counts_exclude_observations_outside_ownership(self):
        observed = {'instruction_offsets': set(range(96, 102)) | set(range(108, 114)),
                    'literal_offsets': set(range(92, 96)) | set(range(104, 108))}
        self.assertEqual(observed_extent_counts(observed, 100, 12),
                         {'decoded_instruction_bytes': 6, 'referenced_literal_bytes': 4})
        self.assertEqual(observed_extent_counts({}, 100, 12), {})

    def test_replacement_does_not_erase_observed_dual_byte_roles(self):
        observed = {'instruction_offsets': set(range(100, 104)),
                    'literal_offsets': set(range(100, 104))}
        self.assertEqual(observed_extent_counts(observed, 100, 4),
                         {'decoded_instruction_bytes': 4, 'referenced_literal_bytes': 4})

    def test_final_overlay_recounts_both_surviving_estimate_remnants(self):
        estimate = {'name': 'estimate', 'rom_offset': 100, 'size': 20,
                    'status': 'mapped_code', 'decoded_instruction_bytes': 14,
                    'referenced_literal_bytes': 4,
                    'instruction_offsets': set(range(100, 114)),
                    'literal_offsets': set(range(116, 120))}
        source = {'name': 'source', 'rom_offset': 108, 'size': 4,
                  'status': 'exact_c', 'instruction_offsets': set(range(108, 112)),
                  'literal_offsets': set()}
        rows = overlay([estimate], [source])
        finalize_extent_observations(rows)
        self.assertEqual([(r['rom_offset'], r['size'], r['decoded_instruction_bytes'],
                           r['referenced_literal_bytes']) for r in rows],
                         [(100, 8, 8, 0), (108, 4, 4, 0), (112, 8, 2, 4)])
        self.assertTrue(all('instruction_offsets' not in r and 'literal_offsets' not in r
                            for r in rows))

    def test_observed_targets_do_not_remove_unproven_callback_bounds(self):
        records = [
            {'rom_offset': 4, 'kind': 'register_veneer_call',
             'targets': [], 'targets_complete': False},
            {'rom_offset': 8, 'kind': 'observed_table_call',
             'targets': [BASE + 100], 'targets_complete': False},
            {'rom_offset': 12, 'kind': 'dynamic_call', 'targets': []},
            {'rom_offset': 16, 'kind': 'observed_table_call',
             'targets': [BASE + 100], 'targets_complete': True},
            {'rom_offset': 20, 'kind': 'register_dispatch',
             'targets': [], 'targets_complete': False},
        ]
        self.assertEqual(unresolved_callback_sites([{'transfer_records': records}]),
                         [4, 8, 12])

    def test_copied_and_rom_aliases_count_one_callback_site(self):
        rows = [{'transfer_records': [
            {'rom_offset': 8, 'site': address, 'kind': 'observed_table_call',
             'targets': [BASE + 100], 'targets_complete': False}]}
            for address in (BASE + 8, 0x03001008)]
        self.assertEqual(unresolved_callback_sites(rows), [8])

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
        self.assertIn('invalid or non-ARM7 instruction', result['issues'])

    def test_ram_alias_uses_original_rom_offset(self):
        scanner = Scanner(bytes.fromhex('000000007047'), [
            {'ram_address': 0x03000000, 'rom_offset': 4, 'size': 2}])
        self.assertEqual(scanner.physical(0x03000000), 4)
        self.assertEqual(scanner.physical(BASE+4), 4)

    def test_pop_then_bx_is_return_not_unknown_callback(self):
        scanner = self.scanner('02bc0847')
        self.assertEqual(scanner.results[(BASE, 'Thumb')]['unresolved_transfers'], set())
