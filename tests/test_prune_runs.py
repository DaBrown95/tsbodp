"""Pruning keeps the run the latest reports name and nothing else."""
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import project
import prune_runs


class PruneTests(unittest.TestCase):
    def setUp(self):
        self.folder = tempfile.TemporaryDirectory()
        root = Path(self.folder.name)
        self.patch = mock.patch.object(project, 'ROOT', root)
        self.patch.start()
        self.paths = project.target_paths('rev1')

    def tearDown(self):
        self.patch.stop()
        self.folder.cleanup()

    def run_folder(self, kind, run_id):
        path = getattr(self.paths, kind) / run_id
        path.mkdir(parents=True)
        return path

    def test_only_reported_run_is_kept(self):
        self.paths.reports.mkdir(parents=True)
        for name in ('pilot', 'build'):
            (self.paths.reports / f'{name}.json').write_text(json.dumps({'run_id': 'new'}))
        keep = [self.run_folder('pilot_runs', 'new'), self.run_folder('rom_runs', 'new')]
        old = [self.run_folder('pilot_runs', 'old'), self.run_folder('rom_runs', 'old')]
        self.assertEqual(prune_runs.stale_runs(self.paths), sorted(old))
        self.assertTrue(all(p.is_dir() for p in keep))

    def test_target_without_reports_keeps_nothing(self):
        stale = self.run_folder('pilot_runs', 'orphan')
        self.assertEqual(prune_runs.stale_runs(self.paths), [stale])


if __name__ == '__main__':
    unittest.main()
