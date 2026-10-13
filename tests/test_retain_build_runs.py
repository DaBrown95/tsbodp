import gzip, importlib.util, json, tempfile, unittest, zipfile, hashlib
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

    def test_roundtrip_retains_sources_receipts_and_current_proofs(self):
        plan = m.make_plan()
        self.assertEqual(len(plan['operations']), 4)
        m.apply(plan)
        for op in plan['operations']:
            self.assertFalse((self.root / op['folder']).exists())
            d = self.root / 'reports/pruned-build-runs' / op['kind'] / Path(op['folder']).name
            self.assertEqual(hashlib.sha256(gzip.decompress((d / 'report.json.gz').read_bytes())).hexdigest(), op['report_sha256'])
            with zipfile.ZipFile(d / 'sources-and-controls.zip') as z:
                self.assertEqual(z.read('changed.c'), b'int example(void){return 2;}')
                self.assertEqual(z.read('inline-glue-control/include/control.h'), b'#define CONTROL 2\n')
                self.assertEqual(z.read('preprocessor.d'), b'source.i: retained-source.c')
                self.assertEqual(z.read('changed.s'), b'nop\n')
                self.assertEqual(z.read('source-inputs/private.h'), b'#define PRIVATE 7\n')
        self.assertTrue((self.root / 'build/pilot/runs' / self.runs[-1] / 'source.o').is_file())

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
