"""Strong byte unions cannot turn weak seeds or owned envelopes into code."""
import copy
import json
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from inventory_census import census, verify_census


class FakeScanner:
    def __init__(self, size=64, copies=()):
        self.data, self.copies = bytes(size), copies

    def physical(self, address):
        if 0x1000 <= address < 0x1000+len(self.data):
            return address-0x1000
        for row in self.copies:
            delta = address-row['ram_address']
            if 0 <= delta < row['size']:
                return row['rom_offset']+delta
        return None


class CensusTests(unittest.TestCase):
    def fixture(self, instructions=None, literals=(), mode='Thumb', address=0x1000):
        scanner = FakeScanner()
        key = address, mode
        entries = {key: dict(evidence={'bounded audit'}, name='actual')}
        results = {key: dict(instructions=instructions or {0x1000: 2, 0x1002: 2},
                             literals=set(literals), issues=set(), return_sites={0x1002},
                             unresolved_transfers=set(), terminal=True)}
        return scanner, entries, results

    def run_census(self, *args, **kwargs):
        result = json.loads(json.dumps(census(*args, **kwargs)))
        self.assertTrue(verify_census(result, len(args[0].data)))
        self.assertEqual(sum(r['size'] for r in result['partition']), len(args[0].data))
        return result

    def test_owned_extent_is_not_instruction_or_denominator(self):
        result = self.run_census(*self.fixture(literals=range(4, 8)),
                                 rows=[dict(rom_offset=0, size=16)],
                                 source_code=[dict(name='source', rom_offset=0, size=12)])
        counts = result['counts']
        self.assertEqual(counts['source_glue_owned_extent_bytes'], 12)
        self.assertEqual(counts['qualified_observed_instruction_union_bytes'], 4)
        self.assertEqual(counts['classification_bytes']['owned_extent_unclassified'], 4)
        self.assertEqual(counts['classification_bytes']['estimated_envelope_unclassified'], 4)
        self.assertFalse(result['single_code_denominator_established'])

    def test_copied_alias_and_shared_tail_are_counted_once(self):
        scanner, entries, results = self.fixture()
        scanner.copies = [dict(name='copy', ram_address=0x2000, rom_offset=0, size=12),
                          dict(name='overlap', ram_address=0x3000, rom_offset=8, size=8)]
        entries[(0x2000, 'Thumb')] = dict(evidence={'audited RAM entry'}, name='alias')
        results[(0x2000, 'Thumb')] = dict(instructions={0x2000: 2, 0x2002: 2, 0x2004: 2}, literals={8, 9})
        entries[(0x1002, 'Thumb')] = dict(evidence={'direct call'}, name='shared')
        results[(0x1002, 'Thumb')] = dict(instructions={0x1002: 2}, literals=set())
        result = self.run_census(scanner, entries, results)
        self.assertEqual(result['counts']['raw_instruction_union_bytes'], 6)
        self.assertEqual(result['unique_physical_entries'], 2)
        self.assertEqual(result['copy_accounting']['installed_byte_sum'], 20)
        self.assertEqual(result['copy_accounting']['unique_physical_source_bytes'], 16)
        self.assertEqual(result['copy_accounting']['repeated_physical_source_bytes'], 4)

    def test_mode_conflict_and_unexplained_data_overlap_are_ambiguous(self):
        scanner, entries, results = self.fixture(literals=(2, 3))
        entries[(0x1000, 'ARM')] = dict(evidence={'startup'}, name='ARM')
        results[(0x1000, 'ARM')] = dict(instructions={0x1000: 4}, literals=set())
        result = self.run_census(scanner, entries, results)
        self.assertEqual(result['counts']['classification_bytes']['ambiguous_mode_conflict'], 4)
        self.assertEqual(result['counts']['nonconflicting_qualified_instruction_bytes'], 0)
        plain = self.run_census(*self.fixture(literals=(2, 3)))
        self.assertEqual(plain['counts']['classification_bytes']['ambiguous_instruction_data_overlap'], 2)

    def test_known_data_instruction_overlap_is_not_approved_dual_use(self):
        result = self.run_census(*self.fixture(), data_regions=[dict(rom_offset=0, size=4)])
        self.assertEqual(result['counts']['classification_bytes']['ambiguous_instruction_known_data'], 4)

    def test_supported_dual_use_retains_both_roles_without_double_count(self):
        note = dict(kind='dual_use', ranges=[[2, 4]], reason='actual code word read', evidence=['load and entry'])
        result = self.run_census(*self.fixture(literals=(2, 3)), quality_annotations=[note])
        self.assertEqual(result['counts']['classification_bytes']['instruction_and_referenced_data_dual_use'], 2)
        self.assertEqual(result['counts']['nonconflicting_qualified_instruction_bytes'], 4)

    def test_context_exclusion_preserves_other_root_and_raw_alternative(self):
        scanner, entries, results = self.fixture()
        entries[(0x1002, 'Thumb')] = dict(evidence={'direct call'}, name='real shared')
        results[(0x1002, 'Thumb')] = dict(instructions={0x1002: 2}, literals=set())
        note = dict(kind='exclude_observation', entry=0x1000, mode='Thumb',
                    instruction_ranges=[[0, 4]], reason='wrong-mode descendants', evidence=['actual mode edge'])
        result = self.run_census(scanner, entries, results, quality_annotations=[note])
        self.assertEqual(result['counts']['raw_instruction_union_bytes'], 4)
        self.assertEqual(result['counts']['qualified_observed_instruction_union_bytes'], 2)
        self.assertEqual(result['counts']['classification_bytes']['contingent_unqualified_observation'], 2)

    def test_literal_exclusion_keeps_raw_reference_count(self):
        note = dict(kind='exclude_observation', entry=0x1000, mode='Thumb', literal_ranges=[[4, 6]],
                    reason='contingent reference', evidence=['closed graph'])
        result = self.run_census(*self.fixture(literals=range(4, 8)), quality_annotations=[note])
        self.assertEqual(result['counts']['raw_referenced_data_union_bytes'], 4)
        self.assertEqual(result['counts']['qualified_referenced_data_union_bytes'], 2)

    def test_weak_evidence_and_snapshot_mismatch_fail_closed(self):
        for evidence in ({'pointer candidate'}, {'candidate call'}, {'bounded audit', 'prologue candidate'}, set()):
            scanner, entries, results = self.fixture()
            entries[(0x1000, 'Thumb')]['evidence'] = evidence
            with self.subTest(evidence=evidence), self.assertRaises(ValueError):
                census(scanner, entries, results)
        scanner, entries, results = self.fixture()
        with self.assertRaises(ValueError):
            census(scanner, {}, results)

    def test_unbacked_partial_instruction_and_outside_literal_rejected(self):
        for instructions, literals in (({0x103e: 4}, ()), ({0x1001: 2}, ()), ({0x1000: 2}, (64,))):
            with self.subTest(instructions=instructions, literals=literals), self.assertRaises(ValueError):
                census(*self.fixture(instructions, literals))
        scanner, entries, results = self.fixture({0x2000: 4}, address=0x2000)
        scanner.copies = [dict(name='short', ram_address=0x2000, rom_offset=0, size=2)]
        with self.assertRaises(ValueError):
            census(scanner, entries, results)

    def test_invalid_ownership_or_estimated_extent_rejected(self):
        for keyword, rows in (('source_code', [dict(rom_offset=0, size=4), dict(rom_offset=2, size=4)]),
                              ('rows', [dict(rom_offset=60, size=8)]),
                              ('data_regions', [dict(rom_offset=-1, size=2)])):
            with self.subTest(keyword=keyword), self.assertRaises(ValueError):
                census(*self.fixture(), **{keyword: rows})

    def test_explicit_data_assembly_owned_extent_does_not_seed_code(self):
        result = self.run_census(*self.fixture(), source_code=[
            dict(name='data glue', rom_offset=8, size=4, mode='data')])
        self.assertEqual(result['counts']['source_glue_owned_extent_bytes'], 4)
        self.assertEqual(result['counts']['classification_bytes']['known_data'], 4)
        self.assertEqual(result['counts']['raw_instruction_union_bytes'], 4)

    def test_verifier_rejects_changed_copy_ownership_and_mode_metadata(self):
        scanner, entries, results = self.fixture()
        scanner.copies = [dict(name='actual', rom_offset=0, size=4, ram_address=0x2000)]
        result = self.run_census(scanner, entries, results)
        changed = copy.deepcopy(result)
        changed['copy_accounting']['unique_physical_source_bytes'] += 4
        with self.assertRaises(ValueError):
            verify_census(changed, 64)
        changed = copy.deepcopy(result)
        changed['entry_boundary_observations'][0]['mode'] = 'ARM'
        with self.assertRaises(ValueError):
            verify_census(changed, 64)

    def test_annotations_cannot_invent_bytes_split_BL_or_falsely_claim_dual_use(self):
        base = dict(reason='actual evidence', evidence=['qualified observation'])
        bad = [dict(kind='exclude_observation', entry=0x1000, mode='Thumb', instruction_ranges=[[4, 6]]),
               dict(kind='exclude_observation', entry=0x1000, mode='Thumb', instruction_ranges=[[0, 1]]),
               dict(kind='exclude_observation', entry=0x1002, mode='Thumb', instruction_ranges=[[0, 2]]),
               dict(kind='dual_use', ranges=[[0, 2]]), dict(kind='unknown')]
        for note in bad:
            with self.subTest(note=note), self.assertRaises(ValueError):
                census(*self.fixture(), quality_annotations=[{**base, **note}])
        with self.assertRaises(ValueError):
            census(*self.fixture({0x1000: 4}), quality_annotations=[{**base, 'kind':'exclude_observation',
                'entry':0x1000, 'mode':'Thumb', 'instruction_ranges':[[0, 2]]}])
        with self.assertRaises(ValueError):
            census(*self.fixture(literals=(0, 1)), quality_annotations=[dict(kind='dual_use', ranges=[[0, 2]])])

    def test_summary_covers_banks_and_partial_last_region(self):
        scanner, entries, results = self.fixture()
        scanner.data = bytes(65539)
        result = self.run_census(scanner, entries, results)
        self.assertEqual([r['size'] for r in result['regions_64KiB']], [65536, 3])
        self.assertEqual(result['regions_64KiB'][-1]['classification_bytes'], {'unresolved': 3})

    def test_verifier_rejects_partition_gaps_overlap_and_count_drift(self):
        result = self.run_census(*self.fixture())
        for modify in (lambda d: d['partition'].pop(),
                       lambda d: d['partition'][0].update(size=5),
                       lambda d: d['counts'].update(raw_instruction_union_bytes=6),
                       lambda d: d['regions_64KiB'][0].update(size=63),
                       lambda d: d['physical_unions']['instruction'].append([3, 5])):
            value = copy.deepcopy(result)
            modify(value)
            with self.assertRaises(ValueError):
                verify_census(value, 64)

    def test_region_confidence_and_evidence_cannot_be_forged(self):
        result = self.run_census(*self.fixture(), rows=[dict(rom_offset=0, size=12)])
        for row in result['partition']:
            profile = result['classification_definitions'][row['classification']]
            self.assertEqual(row['confidence'], profile['confidence'])
            self.assertEqual(row['evidence_basis'], profile['evidence_basis'])
        for modify in (lambda d: d['partition'][0].update(confidence='runtime_proven'),
                       lambda d: d['partition'][-1].update(evidence_basis='complete code exclusion'),
                       lambda d: d['classification_definitions']['unresolved'].update(confidence='high'),
                       lambda d: d['regions_64KiB'][0].update(classification_profiles=[])):
            changed = copy.deepcopy(result)
            modify(changed)
            with self.assertRaises(ValueError):
                verify_census(changed, 64)

    def test_verifier_rejects_completeness_runtime_credit_and_weak_promotion(self):
        result = self.run_census(*self.fixture())
        for key, value in (('complete_code_inventory', True), ('single_code_denominator_established', True),
                           ('recovered_source_credit_changed', True), ('runtime_observations', 1)):
            changed = copy.deepcopy(result)
            changed[key] = value
            with self.subTest(key=key), self.assertRaises(ValueError):
                verify_census(changed, 64)
        result['entry_boundary_observations'][0]['evidence'] = ['pointer candidate']
        with self.assertRaises(ValueError):
            verify_census(result, 64)


if __name__ == '__main__':
    unittest.main()
