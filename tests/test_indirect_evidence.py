"""Reject false table closure, stale producers and misassigned callback columns."""
import hashlib
import importlib.util
import struct
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from indirect_evidence import record_tables, phase_targets, validate_fixed_target, annotate_records, literal_veneers


class IndirectEvidenceTests(unittest.TestCase):
    def table(self, data):
        return dict(name='observed', rom_offset=0, observed_rows=2,
                    record_stride=8, callback_fields=[0], targets_complete=False,
                    evidence=['typed consumer and assignment'],
                    region_sha256=hashlib.sha256(data).hexdigest())

    def test_noncallback_field_is_not_seeded_and_null_is_retained(self):
        data = struct.pack('<4I', 0x101, 0xDEADBEEF, 0, 0xDEADBEEF)
        row = record_tables(data, [self.table(data)], lambda a: 0 if a == 0x100 else None)[0]
        self.assertEqual(row['targets'], [0x101])
        self.assertEqual(row['columns'], {0: [0x101, 0]})
        self.assertFalse(row['targets_complete'])

    def test_stale_prefix_bad_layout_or_false_closure_rejected(self):
        data = struct.pack('<4I', 0x101, 0, 0, 0)
        base = self.table(data)
        for change in ({'region_sha256': '0'*64}, {'targets_complete': True},
                       {'callback_fields': [4, 8]}, {'observed_rows': 3},
                       {'evidence': []}, {'callback_fields': [0, 0]}):
            with self.subTest(change=change), self.assertRaises(ValueError):
                record_tables(data, [{**base, **change}], lambda a: 0)
        with self.assertRaises(ValueError):
            record_tables(data, [base], lambda a: None)

    def test_column_targets_do_not_include_other_phases(self):
        row = dict(entries=[0x101, 0x201, 0x301, 0x401, 0, 0x601],
                   record_stride=12, record_count=2, phase_fields=[0, 4, 8],
                   consumer_fields={'20': 4})
        self.assertEqual(phase_targets(row, 20), [0x200])
        with self.assertRaises(ValueError):
            phase_targets(row, 22)

    def test_changed_source_or_literal_cannot_close_fixed_target(self):
        data = struct.pack('<2I', 0, 0x100)
        owner = dict(name='caller', rom_offset=0, size=8)
        row = dict(owner='caller', rom_offset=0, literal_rom_offset=4,
                   target=0x100, source_sha256='source')
        self.assertEqual(validate_fixed_target(row, data, [owner], lambda f: 'source', lambda a: 0), 0x100)
        for change in ({'source_sha256': 'stale'}, {'target': 0x104},
                       {'rom_offset': 8}, {'literal_rom_offset': 0}):
            with self.subTest(change=change), self.assertRaises(ValueError):
                validate_fixed_target({**row, **change}, data, [owner], lambda f: 'source', lambda a: 0)

    def test_annotations_cannot_invent_an_unseen_transfer(self):
        evidence = [dict(rom_offset=2, target_origin='fixed_literal')]
        fixed = [dict(rom_offset=2, target=0x100)]
        with self.assertRaises(ValueError):
            annotate_records({}, lambda a: a, evidence, fixed)
        result = {'one': {'transfer_records': [dict(site=2, targets_complete=False)]}}
        annotate_records(result, lambda a: a, evidence, fixed)
        record = result['one']['transfer_records'][0]
        self.assertEqual(record['targets'], [0x100])
        self.assertTrue(record['targets_complete'])

    @unittest.skipIf(importlib.util.find_spec('capstone') is None, 'Capstone is needed for veneer decoding')
    def test_literal_veneer_requires_actual_load_register_target_and_adjacency(self):
        from inventory_rom import Scanner
        data = bytes.fromhex('004b1847090000087047')
        scanner = Scanner(data, [])
        row = dict(entry_rom_offset=0, load_rom_offset=0, BX_rom_offset=2,
                   literal_rom_offset=4, target=0x08000009)
        family = dict(rom_offset=0, size=len(data), region_sha256=hashlib.sha256(data).hexdigest(), entries=[row])
        self.assertEqual(literal_veneers(scanner, family), [0x08000000])
        for change in ({'target': 0x08000001}, {'literal_rom_offset': 0},
                       {'BX_rom_offset': 8}, {'entry_rom_offset': 2}):
            with self.subTest(change=change), self.assertRaises(ValueError):
                literal_veneers(scanner, {**family, 'entries': [{**row, **change}]})
