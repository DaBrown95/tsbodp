"""Triage must not turn stale, partial, or rejected experiments into a queue best."""
import hashlib
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import triage


class TriageTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.offset = 0x3D788
        self.name = 'remaining_function'
        self.inventory = {'target': 'us-eu', 'reference_sha256': 'a' * 64,
                          'rows': [{'name': self.name, 'rom_offset': self.offset, 'size': 12,
                                    'mode': 'Thumb', 'runtime_addresses': [0x08000000+self.offset]}]}
        self.progress = {'target': 'us-eu', 'reference_sha256': 'a' * 64,
                         'rows': [{'name': self.name, 'rom_offset': self.offset, 'size': 12,
                                   'status': 'mapped_code'}]}
        self.write('assets/rom-inventory.json', self.inventory)
        self.progress['input_sha256'] = {'assets/rom-inventory.json': triage.sha(self.root / 'assets/rom-inventory.json')}
        self.write('assets/progress.json', self.progress)
        self.write('docs/COMPLETION_BLOCKERS.md', '**1 unowned rows / 12 bytes**\n')
        self.write('include/owner.h', 'extern int owner;\n')

    def write(self, name, data):
        path = self.root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        if isinstance(data, bytes):
            path.write_bytes(data)
        else:
            path.write_text(data if isinstance(data, str) else json.dumps(data))
        return path

    def make_candidate(self, name='trial', size=12, extent=12, differences=2):
        prefix = 'analysis/experiment/' + name
        source = self.write(prefix + '/source.c', 'void remaining_function(void) {}\n')
        metadata = {'name': 'remaining_function', 'rom_offset': self.offset, 'size': extent,
                    'mode': 'Thumb', 'compiler_id': 'agbcc', 'compiler_flags': ['-O2', '-mthumb-interwork'],
                    'source': prefix + '/source.c'}
        self.write(prefix + '/metadata.json', metadata)
        raw = self.write(prefix + '/normal/candidate.bin', b'\x01' * size)
        self.write(prefix + '/normal/linked.elf', b'retained physical artifact fixture')
        self.write(prefix + '/normal/source-inputs/source.c', source.read_bytes())
        header = self.write(prefix + '/normal/include/owner.h', (self.root / 'include/owner.h').read_bytes())
        self.write(prefix + '/normal/header-snapshot.json', {
            'headers': {'owner.h': triage.sha(header)},
            'source_bundle': {'source': 'source.c', 'source_sha256': triage.sha(source), 'source_local_headers': {}}})
        self.write(prefix + '/result.json', {
            'reference_size': extent, 'candidate_size': size,
            'differing_bytes_including_missing_or_extra': differences,
            'candidate_hashes': {'sha256': triage.sha(raw)}, 'source_sha256': triage.sha(source)})
        self.write('analysis/experiment/assessment.json', {'status': 'COMPLETE_NONEXACT',
                                                         'source_findings': ['Conditional source review.']})
        return self.root / prefix

    def row(self):
        return triage.build(self.root)['rows'][0]

    def test_full_comparison_not_inventory_estimate_controls_near_miss(self):
        self.make_candidate(size=14, extent=14, differences=2)
        row = self.row()
        self.assertEqual(row['inventory_bytes'], 12)
        self.assertEqual(row['best_candidate']['comparison_extent_bytes'], 14)
        self.assertEqual(row['status'], 'near-miss')
        self.assertIsNone(row['active_effort_seconds'])
        self.assertIsNone(row['historical_active_effort_seconds'])
        self.assertIsNone(row['search_wall_seconds'])

    def test_missing_bytes_cannot_be_ignored_in_score(self):
        with self.assertRaisesRegex(ValueError, 'Impossible'):
            triage.comparison({'reference_size': 12, 'candidate_size': 8,
                               'differing_bytes_including_missing_or_extra': 2})
        self.make_candidate(size=8, differences=4)
        self.assertEqual(self.row()['status'], 'attempted')

    def test_ambiguous_or_partial_score_does_not_qualify(self):
        with self.assertRaisesRegex(ValueError, 'Missing or ambiguous'):
            triage.comparison({'bytes': 12, 'differences': 0, 'prefix_match': 12})
        with self.assertRaisesRegex(ValueError, 'Missing or ambiguous'):
            triage.comparison([{'reference_size': 12, 'candidate_size': 12,
                                'differing_bytes_including_missing_or_extra': d} for d in (1, 2)])

    def test_semantic_rejection_beats_better_numeric_score(self):
        good = self.make_candidate('good', differences=2)
        bad = self.make_candidate('bad', differences=1)
        self.write('analysis/experiment/assessment.json', {'status': 'COMPLETE', 'results': [
            {'name': 'bad', 'validity_status': 'REJECT_INHERITED_REQUEST_COLLISION'},
            {'name': 'good', 'validity_status': 'SOURCE_REVIEW_PASS'}]})
        row = self.row()
        self.assertEqual(row['best_candidate']['source'], good.relative_to(self.root).as_posix() + '/source.c')
        self.assertEqual(row['excluded_contexts']['Explicit semantic rejection or unqualified source'], 1)
        self.assertTrue((bad / 'source.c').exists())

    def test_changed_source_raw_and_header_are_each_rejected(self):
        for changed in ('source.c', 'normal/candidate.bin', 'normal/include/owner.h'):
            with self.subTest(changed=changed):
                folder = self.make_candidate()
                (folder / changed).write_bytes(b'changed')
                self.assertIsNone(self.row()['best_candidate'])

    def test_current_header_drift_is_not_an_implicit_private_override(self):
        folder = self.make_candidate()
        self.write('include/owner.h', 'extern unsigned owner;\n')
        self.assertIsNone(self.row()['best_candidate'])
        old = self.write('analysis/experiment/private-owner.h', (folder / 'normal/include/owner.h').read_bytes())
        self.write('analysis/experiment/assessment.json', {
            'status': 'COMPLETE', 'private_header': {'path': 'analysis/experiment/private-owner.h',
                                                   'sha256': triage.sha(old)}})
        row = self.row()
        self.assertEqual(row['best_candidate']['private_header_qualification'], 'private-provisional')
        self.assertEqual(row['best_candidate']['header_overrides']['owner.h']['path'],
                         'analysis/experiment/private-owner.h')

    def test_duplicate_and_malformed_inventory_fail_closed(self):
        for replacement in ([self.progress['rows'][0]] * 2,
                            [{**self.progress['rows'][0], 'size': True}],
                            [{**self.progress['rows'][0], 'name': '/outside/root'}]):
            with self.subTest(replacement=replacement), self.assertRaises(ValueError):
                triage.inventory_rows({**self.progress, 'rows': replacement}, self.inventory)

    def test_stale_progress_inventory_pin_fails(self):
        self.write('assets/rom-inventory.json', {**self.inventory, 'extra': True})
        with self.assertRaisesRegex(ValueError, 'stale inventory'):
            triage.build(self.root)

    def test_malformed_candidate_is_attempted_not_untouched_or_best(self):
        folder = self.make_candidate()
        (folder / 'result.json').write_text('{broken')
        row = self.row()
        self.assertEqual(row['status'], 'attempted')
        self.assertIsNone(row['best_candidate'])
        self.assertIn('Malformed evidence JSON', row['excluded_contexts'])

    def test_paths_and_outputs_cannot_escape_or_overwrite_inputs(self):
        for path in ('/outside/root', '../private', 'analysis/../secret', 'C:\\private'):
            with self.subTest(path=path), self.assertRaises(ValueError):
                triage.relative(path)
        report = triage.build(self.root)
        with self.assertRaises(ValueError):
            triage.write_outputs(self.root, report, output='assets/progress.json')
        self.write('config/other.json', 'original')
        (self.root / triage.OUTPUT).symlink_to(self.root / 'config/other.json')
        with self.assertRaises(ValueError):
            triage.write_outputs(self.root, report)
        self.assertEqual((self.root / 'config/other.json').read_text(), 'original')

    def test_portable_record_is_explicit_and_cannot_rescue_changed_local_source(self):
        folder = self.make_candidate()
        report = triage.build(self.root)
        (folder / 'source.c').write_text('changed')
        self.assertIsNone(triage.build(self.root, report)['rows'][0]['best_candidate'])
        shutil.rmtree(self.root / 'analysis')
        portable = triage.build(self.root, report)['rows'][0]
        self.assertEqual(portable['status'], 'near-miss')
        self.assertEqual(portable['best_candidate']['evidence_state'], 'recorded-not-revalidated')
        self.assertIsNone(portable['active_effort_seconds'])

    def test_compiler_mode_and_audio_exception_are_validated(self):
        self.progress['rows'][0]['rom_offset'] = 0x49968
        self.inventory['rows'][0]['rom_offset'] = 0x49968
        self.write('assets/rom-inventory.json', self.inventory)
        self.progress['input_sha256']['assets/rom-inventory.json'] = triage.sha(self.root / 'assets/rom-inventory.json')
        self.write('assets/progress.json', self.progress)
        row = self.row()
        self.assertEqual(row['status'], 'suspected-not-C')
        self.assertEqual(row['compiler_id'], 'gcc302')
        self.assertIn('-mthumb', row['compiler_flags'])

    def test_explicit_search_wall_time_does_not_become_historical_active_effort(self):
        self.write('reports/current-goal/search/ledger.json', {
            'rom_offset': self.offset, 'search_wall_seconds': 123, 'first_timestamp': 1, 'last_timestamp': 99999})
        row = self.row()
        self.assertEqual(row['search_wall_seconds'], 123)
        self.assertIsNone(row['active_effort_seconds'])

    def test_resolver_rechecks_hashes_and_exposes_no_compiler_path(self):
        folder = self.make_candidate()
        report = triage.build(self.root)
        triage.write_outputs(self.root, report)
        resolved = triage.resolve_row(self.root, '0x3D788')
        self.assertEqual(resolved['source'], (folder / 'source.c').resolve())
        self.assertEqual(resolved['function'], 'remaining_function')
        self.assertNotIn('executable', resolved)
        (folder / 'source.c').write_text('changed')
        with self.assertRaisesRegex(ValueError, 'changed'):
            triage.resolve_row(self.root, self.name)

    def test_generation_is_deterministic_and_check_does_not_write(self):
        self.make_candidate()
        report = triage.build(self.root)
        triage.write_outputs(self.root, report)
        self.assertEqual(report, triage.build(self.root, report))
        old = (self.root / triage.OUTPUT).read_bytes()
        self.assertTrue(triage.write_outputs(self.root, report, check=True))
        self.assertEqual(old, (self.root / triage.OUTPUT).read_bytes())
        self.assertEqual(sum(report['totals']['status_inventory_bytes'].values()), 12)

    def test_scan_does_not_enter_tool_checkouts_or_output_snapshots(self):
        self.make_candidate()
        self.write('analysis/compiler-build/gcc/metadata.json', {})
        self.write('analysis/experiment/trial/normal/metadata.json', {})
        self.assertEqual(len(triage.bounded_metadata(self.root)), 1)

    def make_search_validation(self):
        job_prefix = 'analysis/permuter/job'
        folder = job_prefix + '/validation-1'
        source = self.write(job_prefix + '/improvement.c', 'void remaining_function(void) {}\n')
        raw = self.write(folder + '/candidate.bin', b'\x02' * 12)
        self.write(folder + '/source.c', source.read_bytes())
        self.write(folder + '/linked.elf', b'linked artifact fixture')
        header = self.write(job_prefix + '/context/include/owner.h', (self.root / 'include/owner.h').read_bytes())
        snapshot = self.write(job_prefix + '/context/header-snapshot.json', {
            'headers': {'owner.h': triage.sha(header)}, 'source_bundle': {'source_local_headers': {}}})
        job = self.write(job_prefix + '/setup.json', {
            'function': {'name': self.name, 'rom_offset': self.offset, 'size': 12, 'mode': 'Thumb',
                         'compiler_flags': ['-O2', '-mthumb-interwork']},
            'mode': 'Thumb', 'execution_address': self.offset + 0x08000000,
            'reference_rom_sha256': 'a' * 64, 'safe_weights_reviewed': True,
            'full_byte_validation_required': True,
            'immutable_inputs': [{'path': snapshot.relative_to(self.root).as_posix(), 'sha256': triage.sha(snapshot)},
                                 {'path': 'include/owner.h', 'sha256': triage.sha(header)}]})
        receipt = self.write(folder + '/result.json', {
            'status': 'FULL_BYTES_MATCH_REVIEW_REQUIRED',
            'comparison': {'reference_size': 12, 'candidate_size': 12,
                           'differing_bytes_including_missing_or_extra': 0,
                           'candidate_hashes': {'sha256': triage.sha(raw)}},
            'job_manifest': {'path': job.relative_to(self.root).as_posix(), 'sha256': triage.sha(job)},
            'candidate_source': {'path': source.relative_to(self.root).as_posix(), 'sha256': triage.sha(source)}})
        return source, receipt

    def test_fresh_search_full_comparison_is_retained_without_source_promotion(self):
        self.make_candidate(size=8, differences=4)
        self.make_search_validation()
        row = self.row()
        self.assertEqual(row['status'], 'attempted')
        self.assertEqual(row['best_candidate']['full_byte_differences'], 4)
        self.assertEqual(row['search_best']['full_byte_differences'], 0)
        self.assertEqual(row['search_best']['source_review'], 'pending')
        self.assertEqual(row['search_best']['source_credit'], 0)

    def test_review_rejects_search_even_when_full_bytes_match(self):
        source, receipt = self.make_search_validation()
        original_source = source.read_bytes()
        record = json.loads(receipt.read_text())
        record['source_valid_under_recorded_premises'] = False
        record['source_review'] = 'REJECT_UNCONSUMED_HARD_REGISTER_ADDRESS'
        receipt.write_text(json.dumps(record))
        report = triage.build(self.root)
        self.assertIsNone(report['rows'][0]['search_best'])
        self.assertEqual(report['scan']['rejected_search_validations'], 1)
        self.assertEqual(source.read_bytes(), original_source)
        self.assertEqual(json.loads(receipt.read_text())['comparison']
                         ['differing_bytes_including_missing_or_extra'], 0)

    def test_changed_search_source_or_header_cannot_reuse_validation(self):
        source, receipt = self.make_search_validation()
        source.write_text('changed')
        self.assertIsNone(self.row()['search_best'])
        self.make_search_validation()
        self.write('include/owner.h', 'extern unsigned owner;\n')
        report = triage.build(self.root)
        self.assertIsNone(report['rows'][0]['search_best'])
        self.assertEqual(report['scan']['rejected_search_validations'], 1)


if __name__ == '__main__':
    unittest.main()
