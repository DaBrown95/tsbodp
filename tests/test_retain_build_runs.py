import importlib.util, json, tempfile, unittest
from pathlib import Path
spec = importlib.util.spec_from_file_location('prune', str(Path(__file__).resolve().parents[1] / 'tools/retain_build_runs.py'))
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)

class PruneTests(unittest.TestCase):

    def setUp(self):
        self.t = tempfile.TemporaryDirectory()
        m.ROOT = Path(self.t.name).resolve()
        self.root = m.ROOT
        (self.root / m.BASE).mkdir(parents=True)
        (self.root / 'reports/us-eu').mkdir(parents=True, exist_ok=True)
        self.runs = ['20261012T00000' + str(i) + 'Z-' + format(i, '08x') for i in range(4)]
        for kind, parent in [('pilot', 'build/pilot/runs'), ('build', 'build/us-eu/runs')]:
            for run in self.runs:
                p = self.root / parent / run
                p.mkdir(parents=True)
                (p / 'report.json').write_text(json.dumps({'run_id': run, 'accepted': True, 'reference_sha256': m.REFERENCE}))
                (p / 'source.c').write_text('int example(void){return 1;}')
                (p / 'changed.c').write_text('int example(void){return 2;}')
                (p / 'source.o').write_bytes(b'obsolete')
                (p / 'header-snapshot.json').write_text('{}')
                (p / 'preprocessor.d').write_text('source.i: retained-source.c')
                project = p / 'include'
                project.mkdir()
                (project / 'public.h').write_text('#define PUBLIC 1\n')
                control = p / 'inline-glue-control/include'
                control.mkdir(parents=True)
                (control / 'control.h').write_text('#define CONTROL 2\n')
                (p / 'changed.s').write_text('nop\n')
                local = p / 'source-inputs'
                local.mkdir()
                (local / 'private.h').write_text('#define PRIVATE 7\n')
            (self.root / f'reports/us-eu/{kind}.json').write_text(json.dumps({'run_id': self.runs[-1]}))

    def tearDown(self):
        self.t.cleanup()

    def test_duplicate_runs_retired_without_archives_and_current_proof_intact(self):
        plan = m.make_plan()
        self.assertEqual(len(plan['operations']), 6)
        self.assertEqual(plan['held_runs'], [])
        m.apply(plan)
        for op in plan['operations']:
            self.assertFalse((self.root / op['folder']).exists())
        self.assertFalse((self.root / 'reports/pruned-build-runs').exists())
        for kind, parent in [('pilot', 'build/pilot/runs'), ('build', 'build/us-eu/runs')]:
            self.assertTrue((self.root / parent / self.runs[-1] / 'source.o').is_file())
            self.assertTrue((self.root / parent / self.runs[-1] / 'changed.c').is_file())
            self.assertEqual(plan['protected_runs'][kind], [self.runs[-1]])
        journal = next((self.root / m.BASE).glob('prune-*.jsonl'))
        records = [json.loads(line) for line in journal.read_text().splitlines()]
        self.assertEqual(sum(record['event'] == 'completed' for record in records), 6)

    def test_unique_source_control_and_project_header_are_held(self):
        for filename in ('source.c', 'changed.c', 'include/public.h'):
            with self.subTest(filename=filename):
                run = self.root / 'build/pilot/runs' / self.runs[0]
                p = run / filename
                original = p.read_bytes()
                p.write_bytes(b'unique attempt')
                plan = m.make_plan()
                held = [item for item in plan['held_runs'] if item['folder'] == run.relative_to(self.root).as_posix()]
                self.assertEqual(len(held), 1)
                self.assertIn(filename, held[0]['unique_inputs'])
                self.assertNotIn(held[0]['folder'], [item['folder'] for item in plan['operations']])
                p.write_bytes(original)

    def test_completed_journal_does_not_repeat_expanded_input_maps(self):
        for parent in ('build/pilot/runs', 'build/us-eu/runs'):
            for run in self.runs:
                for index in range(256):
                    (self.root / parent / run / 'include' / ('duplicate_%03d.h' % index)).write_text('#define SAME 1\n')
        plan = m.make_plan()
        self.assertGreater(len(json.dumps(plan)), 100000)
        m.apply(plan)
        journal = next((self.root / m.BASE).glob('prune-*.jsonl'))
        self.assertLess(journal.stat().st_size, 16384)
        prepared = [json.loads(line) for line in journal.read_text().splitlines()
                    if json.loads(line)['event'] == 'prepared']
        self.assertEqual(len(prepared), len(plan['operations']))
        for record, operation in zip(prepared, plan['operations']):
            self.assertNotIn('retained_input_pins', record)
            self.assertEqual(record['retained_input_count'], len(operation['retained_input_pins']))
            self.assertEqual(len(record['retained_input_pins_sha256']), 64)
            self.assertEqual(record['report_sha256'], operation['report_sha256'])
            self.assertFalse((self.root / operation['folder']).exists())
        self.assertTrue((self.root / 'build/pilot/runs' / self.runs[-1] / 'include/duplicate_255.h').is_file())

    def test_generated_metadata_does_not_require_archiving_duplicate_inputs(self):
        p = self.root / 'build/pilot/runs' / self.runs[0]
        (p / 'header-snapshot.json').write_text('{"historical_receipt": true}')
        (p / 'preprocessor.d').write_text('old/run/path/source.i: old/run/path/source.c')
        self.assertIn(p.relative_to(self.root).as_posix(), [op['folder'] for op in m.make_plan()['operations']])

    def test_failed_run_excluded(self):
        p = self.root / 'build/pilot/runs' / self.runs[0] / 'report.json'
        r = json.loads(p.read_text())
        r['accepted'] = False
        p.write_text(json.dumps(r))
        self.assertNotIn(str(p.parent.relative_to(self.root)), [o['folder'] for o in m.make_plan()['operations']])

    def test_different_reference_excluded(self):
        p = self.root / 'build/pilot/runs' / self.runs[0] / 'report.json'
        r = json.loads(p.read_text())
        r['reference_sha256'] = 'changed'
        p.write_text(json.dumps(r))
        self.assertNotIn(str(p.parent.relative_to(self.root)), [o['folder'] for o in m.make_plan()['operations']])

    def test_current_proof_change_rejected_before_removal(self):
        plan = m.make_plan()
        (self.root / 'reports/us-eu/pilot.json').write_text(json.dumps({'run_id': 'new'}))
        self.assertRaises(ValueError, m.apply, plan)
        self.assertTrue((self.root / plan['operations'][0]['folder']).exists())

    def test_current_proof_input_change_rejected_before_removal(self):
        plan = m.make_plan()
        p = self.root / 'build/pilot/runs' / self.runs[-1] / 'source.c'
        p.write_text('changed current input')
        self.assertRaises(ValueError, m.apply, plan)
        self.assertTrue((self.root / plan['operations'][0]['folder']).exists())

    def test_current_proof_must_be_accepted(self):
        p = self.root / 'build/pilot/runs' / self.runs[-1] / 'report.json'
        r = json.loads(p.read_text())
        r['accepted'] = False
        p.write_text(json.dumps(r))
        self.assertRaises(ValueError, m.make_plan)

    def test_new_pilot_cannot_retire_the_pilot_of_the_current_full_proof(self):
        (self.root / 'reports/us-eu/pilot.json').write_text(json.dumps({'run_id': self.runs[-2]}))
        self.assertRaises(ValueError, m.make_plan)
        self.assertTrue((self.root / 'build/pilot/runs' / self.runs[-1] / 'source.o').is_file())

    def test_forged_plan_cannot_remove_unique_attempt(self):
        plan = m.make_plan()
        op = plan['operations'][0]
        p = self.root / op['folder'] / 'source.c'
        p.write_text('unique source')
        op['retained_input_pins'] = m.retained_inputs(p.parent)
        self.assertRaises(ValueError, m.apply, plan)
        self.assertTrue(p.is_file())

    def test_changed_receipt_rejected(self):
        plan = m.make_plan()
        p = self.root / plan['operations'][0]['folder'] / 'report.json'
        p.write_text(p.read_text() + ' ')
        self.assertRaises(ValueError, m.apply, plan)
        self.assertTrue(p.exists())

    def test_symlink_rejected(self):
        p = self.root / 'build/pilot/runs' / self.runs[0]
        (p / 'link').symlink_to(self.root / 'reports/us-eu/pilot.json')
        self.assertRaises(ValueError, m.make_plan)

    def test_escaped_path_rejected(self):
        plan = m.make_plan()
        plan['operations'][0]['folder'] = 'reports/us-eu'
        self.assertRaises(ValueError, m.apply, plan)

    def test_protected_run_rejected(self):
        plan = m.make_plan()
        op = plan['operations'][0]
        op['folder'] = 'build/pilot/runs/' + self.runs[-1]
        op['report_sha256'] = m.sha(self.root / op['folder'] / 'report.json')
        self.assertRaises(ValueError, m.apply, plan)

    def test_changed_source_is_not_removed(self):
        plan = m.make_plan()
        p = self.root / plan['operations'][0]['folder'] / 'source.c'
        p.write_text('new unique input')
        self.assertRaises(ValueError, m.apply, plan)
        self.assertTrue(p.exists())

    def test_modified_protection_list_rejected(self):
        plan = m.make_plan()
        plan['protected_runs']['pilot'] = []
        self.assertRaises(ValueError, m.apply, plan)

    def test_symlinked_parent_rejected(self):
        root = self.root / 'build/pilot'
        runs = root / 'runs'
        moved = root / 'moved'
        runs.rename(moved)
        runs.symlink_to(moved, target_is_directory=True)
        self.assertRaises(ValueError, m.make_plan)
if __name__ == '__main__':
    unittest.main()
