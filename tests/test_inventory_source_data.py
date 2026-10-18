"""Pinned source-data roles add no credit and cannot hide rooted execution."""
import copy
import hashlib
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from inventory_rom import source_owned_data_regions
from inventory_census import census, verify_census


class SourceDataTests(unittest.TestCase):
    def fixture(self):
        data = bytes.fromhex('7047000000000000')
        owner = dict(name='owned', rom_offset=0, size=8, source='actual.c')
        row = dict(name='alignment', owner='owned', rom_offset=2, size=2,
                   role='alignment', source_sha256='source',
                   region_sha256=hashlib.sha256(data[2:4]).hexdigest(),
                   evidence=['Actual source output/native span; no execution exclusion.'])
        return data, [owner], row

    def validate(self, row, data=None):
        original, owners, unused = self.fixture()
        return source_owned_data_regions(original if data is None else data,
                                         [row], owners, lambda owner: 'source')

    def test_fixed_region_retains_metadata_without_mutating_input(self):
        data, owners, row = self.fixture()
        before = copy.deepcopy(row)
        self.assertEqual(self.validate(row), [{**row, 'status': 'mapped_data'}])
        self.assertEqual(row, before)
        self.assertEqual(source_owned_data_regions(data, [], owners,
                                                 lambda owner: 'source'), [])

    def test_stale_source_or_reference_hash_is_rejected(self):
        data, unused, row = self.fixture()
        for change in [dict(source_sha256='stale'), dict(region_sha256='stale')]:
            with self.subTest(change=change), self.assertRaises(ValueError):
                self.validate({**row, **change})
        with self.assertRaises(ValueError):
            self.validate(row, data=data[:2] + b'changed')

    def test_unknown_owner_and_invalid_owned_bounds_are_rejected(self):
        unused, unused2, row = self.fixture()
        for change in [dict(owner='missing'), dict(owner=[]),
                       dict(rom_offset=7, size=2), dict(rom_offset=-1),
                       dict(size=0), dict(rom_offset=True), dict(size=2.0),
                       dict(role='instruction'), dict(evidence=[]),
                       dict(evidence=[''])]:
            with self.subTest(change=change), self.assertRaises(ValueError):
                self.validate({**row, **change})
        data, owners, unused = self.fixture()
        for invalid in [None, {}, [None]]:
            with self.subTest(invalid=invalid), self.assertRaises(ValueError):
                source_owned_data_regions(data, invalid, owners, lambda owner: 'source')
        # Inside the ROM but outside the named owner's extent: ROM bounds alone
        # must not make an unrelated span eligible for source-owned provenance.
        longer_rom = data + bytes(8)
        outside_owner = {**row, 'rom_offset': 8,
                         'region_sha256': hashlib.sha256(longer_rom[8:10]).hexdigest()}
        with self.assertRaises(ValueError):
            source_owned_data_regions(longer_rom, [outside_owner], owners,
                                      lambda owner: 'source')

    def test_duplicate_names_and_overlapping_spans_are_rejected(self):
        data, owners, row = self.fixture()
        # Isolate duplicate naming from overlap so either missing check fails.
        for other in [{**row, 'rom_offset': 4}, {**row, 'name': 'different'}]:
            with self.subTest(other=other), self.assertRaises(ValueError):
                source_owned_data_regions(data, [row, other], owners,
                                          lambda owner: 'source')

    def census_with(self, region):
        data, owners, unused = self.fixture()

        class FakeScanner:
            copies = []

            def physical(self, address):
                return address - 0x1000 if 0x1000 <= address < 0x1008 else None

        scanner = FakeScanner()
        scanner.data = data
        key = 0x1000, 'Thumb'
        entries = {key: dict(evidence={'bounded audit'}, name='owned')}
        observations = {key: dict(instructions={0x1000: 2}, literals=set(),
                                 issues=set(), return_sites={0x1000}, terminal=True)}
        result = census(scanner, entries, observations, source_code=owners,
                        data_regions=[] if region is None else self.validate(region))
        self.assertTrue(verify_census(result, len(data)))
        return result

    def test_role_changes_unknown_bytes_without_credit_or_denominator(self):
        unused, unused2, row = self.fixture()
        before, after = self.census_with(None), self.census_with(row)
        self.assertEqual(before['counts']['classification_bytes']['owned_extent_unclassified'], 6)
        self.assertEqual(after['counts']['classification_bytes']['owned_extent_unclassified'], 4)
        self.assertEqual(after['counts']['classification_bytes']['known_data'], 2)
        for result in [before, after]:
            self.assertEqual(result['counts']['qualified_observed_instruction_union_bytes'], 2)
            self.assertEqual(result['counts']['source_glue_owned_extent_bytes'], 8)
            self.assertFalse(result['complete_code_inventory'])
            self.assertFalse(result['single_code_denominator_established'])
            self.assertFalse(result['recovered_source_credit_changed'])

    def test_known_data_overlap_preserves_instruction_conflict(self):
        data, unused, row = self.fixture()
        row = {**row, 'rom_offset': 0,
               'region_sha256': hashlib.sha256(data[:2]).hexdigest()}
        result = self.census_with(row)
        self.assertEqual(result['counts']['classification_bytes']['ambiguous_instruction_known_data'], 2)
        self.assertEqual(result['counts']['qualified_observed_instruction_union_bytes'], 2)
        self.assertFalse(result['complete_code_inventory'])
