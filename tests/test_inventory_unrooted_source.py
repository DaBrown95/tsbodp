"""Owning a source extent must not manufacture its incoming CFG evidence."""
import copy
import json
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from inventory_rom import BASE, Scanner, seed_source_owners
from inventory_census import census, verify_census
from inventory_partition import overlay


class UnrootedSourceTests(unittest.TestCase):
    def fixture(self):
        data = bytearray(32)
        # A leaf reads its own pool and returns; no original caller is supplied.
        data[8:16] = bytes.fromhex('0048704734120000')
        owner = dict(name='unrooted', rom_offset=8, size=8, mode='Thumb',
                     cfg_root=False, cfg_root_reason='Incoming evidence absent.')
        return data, owner

    def measure(self, scanner, owners):
        scanner.drain()
        result = census(scanner, scanner.entries, scanner.results, source_code=owners)
        self.assertTrue(verify_census(result, len(scanner.data)))
        return result

    def test_source_owner_does_not_seed_code_pool_or_audited_entry(self):
        data, owner = self.fixture()
        scanner = Scanner(bytes(data), [])
        roots = seed_source_owners(scanner, [owner], [], [])
        self.assertEqual(roots, [])
        self.assertEqual(overlay([], roots), [])
        result = self.measure(scanner, [owner])
        self.assertEqual(result['entry_boundary_observations'], [])
        self.assertEqual(result['counts']['qualified_observed_instruction_union_bytes'], 0)
        self.assertEqual(result['counts']['qualified_referenced_data_union_bytes'], 0)
        self.assertEqual(result['counts']['source_glue_owned_extent_bytes'], 8)
        self.assertEqual(result['counts']['classification_bytes']['owned_extent_unclassified'], 8)

    def test_missing_or_true_root_setting_preserves_existing_audits(self):
        data, owner = self.fixture()
        for setting in ('missing', True):
            with self.subTest(setting=setting):
                row = copy.deepcopy(owner)
                if setting == 'missing':
                    row.pop('cfg_root')
                else:
                    row['cfg_root'] = setting
                scanner = Scanner(bytes(data), [])
                roots = seed_source_owners(scanner, [row], [], [])
                self.assertEqual(roots, [row])
                result = self.measure(scanner, [row])
                self.assertEqual(result['counts']['qualified_observed_instruction_union_bytes'], 4)
                self.assertEqual(result['counts']['qualified_referenced_data_union_bytes'], 4)

    def test_independent_original_call_still_roots_an_opted_out_owner(self):
        data, owner = self.fixture()
        # BL at0 to8, followed by a return. The target is the same literal leaf.
        data[:6] = bytes.fromhex('00f002f87047')
        scanner = Scanner(bytes(data), [])
        seed_source_owners(scanner, [owner], [], [])
        scanner.seed(BASE, 'Thumb', 'startup', 'caller')
        result = self.measure(scanner, [owner])
        self.assertIn('direct call', scanner.entries[(BASE+8, 'Thumb')]['evidence'])
        target = next(r for r in result['entry_boundary_observations']
                      if r['entry_rom_offset'] == 8)
        self.assertEqual(target['qualified_instruction_intervals'], [(8, 12)])
        self.assertEqual(target['referenced_data_intervals'], [(12, 16)])
        self.assertEqual(result['counts']['source_glue_owned_extent_bytes'], 8)

    def test_opt_out_preserves_independent_data_observations(self):
        data, owner = self.fixture()
        # Another rooted leaf loads a word inside the source-owned extent.
        data[:4] = bytes.fromhex('01487047')
        scanner = Scanner(bytes(data), [])
        seed_source_owners(scanner, [owner], [], [])
        scanner.seed(BASE, 'Thumb', 'startup', 'data_reader')
        result = self.measure(scanner, [owner])
        self.assertEqual(result['counts']['qualified_observed_instruction_union_bytes'], 4)
        cell = next(r for r in result['partition'] if r['rom_offset'] <= 8 < r['rom_offset']+r['size'])
        self.assertEqual(cell['classification'], 'strong_rooted_referenced_data')
        self.assertIn('source_owned', cell['roles'])

    def test_source_mode_does_not_veto_an_independent_ARM_root(self):
        data, owner = self.fixture()
        data[8:12] = bytes.fromhex('1eff2fe1')  # ARM BX LR.
        scanner = Scanner(bytes(data), [])
        seed_source_owners(scanner, [owner], [], [])
        scanner.seed(BASE+8, 'ARM', 'startup', 'independent_ARM_entry')
        result = self.measure(scanner, [owner])
        cell = next(r for r in result['partition'] if r['rom_offset'] == 8)
        self.assertEqual(cell['classification'], 'strong_rooted_instruction')
        self.assertIn('ARM', cell['roles'])
        self.assertNotIn('Thumb', cell['roles'])

    def test_bad_boolean_and_missing_explanation_fail_before_any_seed(self):
        data, owner = self.fixture()
        for value in (None, 0, 1, 'false', [], {}):
            with self.subTest(value=value):
                scanner = Scanner(bytes(data), [])
                with self.assertRaises(ValueError):
                    seed_source_owners(scanner, [{**owner, 'cfg_root': value}], [], [])
                self.assertEqual(scanner.entries, {})
        for reason in (None, '', '  ', 1):
            with self.subTest(reason=reason):
                with self.assertRaises(ValueError):
                    seed_source_owners(Scanner(bytes(data), []), [{**owner, 'cfg_root_reason': reason}], [], [])

    def test_actual_two_owner_declarations_have_no_implicit_root(self):
        root = Path(__file__).resolve().parents[1]
        manifest = json.loads((root/'config/build-us-eu.json').read_text())
        owners = [r for r in manifest['functions']
                  if r['name'] in ('display_replace_mode_control', 'display_replace_layer_control')]
        self.assertEqual([(r['rom_offset'], r['size']) for r in owners], [(0xD628, 36), (0xD64C, 36)])
        scanner = Scanner(bytes(0xD670), [])
        self.assertEqual(seed_source_owners(scanner, owners, [], []), [])
        self.assertEqual(scanner.entries, {})


if __name__ == '__main__':
    unittest.main()
