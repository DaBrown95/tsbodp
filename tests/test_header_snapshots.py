"""Snapshot selection must not hide dependencies or leave stale proof inputs."""
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from header_snapshots import snapshot_headers


class HeaderSnapshotTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.includes = self.root / 'project'
        self.includes.mkdir()
        self.output = self.root / 'trial' / 'include'
        self.source = self.root / 'source.c'
        (self.includes / 'unused.h').write_text('unused\n')

    def snapshot(self, text):
        self.source.write_text(text)
        return snapshot_headers(self.source, self.output, self.includes)

    def test_nested_relative_cycle_and_inactive_branch_retained(self):
        (self.includes / 'nested').mkdir()
        (self.includes / 'nested' / 'a.h').write_text('#include "../b.h"\n')
        (self.includes / 'b.h').write_text('#include "nested/a.h"\n')
        receipt = self.snapshot('#if 0\n#include "nested/a.h"\n#endif\n')
        self.assertEqual(set(receipt['headers']), {'nested/a.h', 'b.h'})
        self.assertFalse((self.output / 'unused.h').exists())

    def test_macro_and_include_next_use_conservative_fallback(self):
        (self.includes / 'dependency.h').write_text('value\n')
        for text in ['#include HEADER\n', '#include_next "dependency.h"\n']:
            with self.subTest(text=text):
                receipt = self.snapshot(text)
                self.assertEqual(receipt['selection'], 'all project headers')
                self.assertIn('dependency.h', receipt['headers'])

    def test_source_local_dependency_does_not_hide_project_headers(self):
        (self.root / 'local.h').write_text('#include "unused.h"\n')
        self.assertEqual(self.snapshot('#include "local.h"\n')['selection'], 'all project headers')

    def test_deleted_header_does_not_survive_reused_trial_folder(self):
        dependency = self.includes / 'dependency.h'
        dependency.write_text('value\n')
        self.snapshot('#include "dependency.h"\n')
        dependency.unlink()
        receipt = self.snapshot('#include "dependency.h"\n')
        self.assertEqual(receipt['selection'], 'all project headers')
        self.assertFalse((self.output / 'dependency.h').exists())

    def test_snapshot_is_independent_of_later_live_changes(self):
        dependency = self.includes / 'dependency.h'
        dependency.write_text('before\n')
        receipt = self.snapshot('#include "dependency.h"\n')
        dependency.write_text('after\n')
        self.assertEqual((self.output / 'dependency.h').read_text(), 'before\n')
        self.assertEqual(json.loads((self.output.parent / 'header-snapshot.json').read_text()), receipt)

    def test_comments_strings_and_line_splicing_do_not_hide_include(self):
        (self.includes / 'dependency.h').write_text('value\n')
        receipt = self.snapshot('char *s="/*";\n/* #include "unused.h" */\n'
                                '#inc\\\nlude "dependency.h" // tail\nchar *t="*/";\n')
        self.assertEqual(set(receipt['headers']), {'dependency.h'})
