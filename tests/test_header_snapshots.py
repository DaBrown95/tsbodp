"""Snapshot selection must not hide dependencies or leave mutable proof inputs."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from header_snapshots import (snapshot_headers, retained_source, verify_snapshot_inputs,
                              verify_preprocessor_dependencies)


class HeaderSnapshotTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name).resolve()
        self.includes = self.root / 'project'
        self.includes.mkdir()
        self.output = self.root / 'trial' / 'include'
        self.source = self.root / 'source.c'
        (self.includes / 'unused.h').write_text('unused\n')

    def snapshot(self, text):
        self.source.write_text(text)
        return snapshot_headers(self.source, self.output, self.includes)

    def bundle(self, receipt):
        return retained_source(receipt, self.output).parent

    def dependencies(self, receipt, paths):
        # The preprocessor's Make syntax escapes spaces/# and doubles dollars.
        words = [str(path).replace('\\', '\\\\').replace(' ', '\\ ')
                 .replace('#', '\\#').replace('$', '$$') for path in paths]
        output = self.output.parent / 'preprocessor.d'
        output.write_text('snapshot: ' + ' \\\n '.join(words) + '\n')
        return verify_preprocessor_dependencies(receipt, self.output, output)

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

    def test_private_closure_avoids_unrelated_project_copies(self):
        (self.root / 'private.h').write_text('#include "nested/local.h"\n')
        (self.root / 'nested').mkdir()
        (self.root / 'nested/local.h').write_text('#include "dependency.h"\n')
        (self.includes / 'dependency.h').write_text('value\n')
        receipt = self.snapshot('#include "private.h"\n')
        self.assertEqual(receipt['selection'], 'literal include closure')
        self.assertEqual(set(receipt['headers']), {'dependency.h'})
        self.assertEqual(set(receipt['source_bundle']['source_local_headers']),
                         {'private.h', 'nested/local.h'})
        self.assertFalse((self.output / 'unused.h').exists())
        self.assertEqual((self.bundle(receipt) / 'private.h').read_text(),
                         (self.root / 'private.h').read_text())

    def test_local_cycles_and_inactive_branch_are_retained(self):
        (self.root / 'nested').mkdir()
        (self.root / 'nested/a.h').write_text('#include "../b.h"\n')
        (self.root / 'b.h').write_text('#include "nested/a.h"\n')
        receipt = self.snapshot('#if 0\n#include "nested/a.h"\n#endif\n')
        self.assertEqual(set(receipt['source_bundle']['source_local_headers']), {'nested/a.h', 'b.h'})
        self.assertEqual(receipt['headers'], {})

    def test_quotes_shadow_project_and_angles_use_project(self):
        (self.root / 'same.h').write_text('local\n')
        (self.includes / 'same.h').write_text('project\n')
        receipt = self.snapshot('#include "same.h"\n#include <same.h>\n')
        self.assertEqual((self.bundle(receipt) / 'same.h').read_text(), 'local\n')
        self.assertEqual((self.output / 'same.h').read_text(), 'project\n')
        self.assertEqual(set(receipt['headers']), {'same.h'})

    def test_private_macro_fallback_pins_bounded_local_headers(self):
        (self.root / 'hidden.h').write_text('#include "dependency.h"\n')
        (self.includes / 'dependency.h').write_text('value\n')
        receipt = self.snapshot('#define HEADER "hidden.h"\n#include HEADER\n')
        self.assertEqual(receipt['selection'], 'all project headers')
        self.assertIn('hidden.h', receipt['source_bundle']['source_local_headers'])
        self.assertEqual((self.bundle(receipt) / 'hidden.h').read_text(),
                         (self.root / 'hidden.h').read_text())

    def test_literal_local_extension_is_retained(self):
        (self.root / 'local.inc').write_text('value\n')
        receipt = self.snapshot('#include "local.inc"\n')
        self.assertIn('local.inc', receipt['source_bundle']['source_local_headers'])

    def test_local_bundle_limits_bound_broad_fallback_and_literal_inputs(self):
        for name in ('a.h', 'b.h'):
            (self.root / name).write_text('longer value\n')
        with patch('header_snapshots.MAX_LOCAL_HEADERS', 1):
            with self.assertRaisesRegex(ValueError, 'file or byte limit'):
                self.snapshot('#include UNKNOWN\n')
        with patch('header_snapshots.MAX_LOCAL_BYTES', 40):
            with self.assertRaisesRegex(ValueError, 'file or byte limit'):
                self.snapshot('#include "a.h"\n#include "b.h"\n')
        (self.root / 'one/two').mkdir(parents=True)
        with patch('header_snapshots.MAX_LOCAL_DIRECTORIES', 1):
            with self.assertRaisesRegex(ValueError, 'directory limit'):
                self.snapshot('#include UNKNOWN\n')

    def test_escaping_literal_and_symlink_inputs_fail(self):
        outside = self.root.parent / ('outside-' + self.root.name + '.h')
        outside.write_text('outside\n')
        self.addCleanup(outside.unlink)
        (self.root / 'escape.h').symlink_to(outside)
        for include in ['"../' + outside.name + '"', '"' + str(outside) + '"',
                        '"escape.h"', '<../outside.h>']:
            with self.subTest(include=include):
                with self.assertRaisesRegex(ValueError, 'escape|symlink'):
                    self.snapshot('#include ' + include + '\n')

    def test_private_relative_project_bypass_is_rejected(self):
        local = self.root / 'private'
        local.mkdir()
        source = local / 'source.c'
        source.write_text('#include "../project/unused.h"\n')
        with self.assertRaisesRegex(ValueError, 'escapes'):
            snapshot_headers(source, self.output, self.includes)

    def test_fallback_does_not_follow_symlink_directories(self):
        (self.root / 'aliased').symlink_to(self.includes, target_is_directory=True)
        with self.assertRaisesRegex(ValueError, 'symlink directory'):
            self.snapshot('#include UNKNOWN\n')

    def test_output_containing_or_inside_live_project_preserves_inputs(self):
        for output_name in ('include', 'source-inputs'):
            with self.subTest(output_name=output_name):
                proof = self.root / output_name
                output = proof / 'include'
                contained = proof / output_name / 'live-project'
                contained.mkdir(parents=True)
                header = contained / 'live.h'
                header.write_text('live project input\n')
                self.source.write_text('void f(void) {}\n')
                with self.assertRaisesRegex(ValueError, 'overlaps'):
                    snapshot_headers(self.source, output, contained)
                self.assertEqual(header.read_text(), 'live project input\n')
        nested_output = self.includes / 'generated/include'
        with self.assertRaisesRegex(ValueError, 'overlaps'):
            snapshot_headers(self.source, nested_output, self.includes)
        self.assertEqual((self.includes / 'unused.h').read_text(), 'unused\n')

    def test_destination_and_parent_symlinks_preserve_other_proof(self):
        protected = self.root / 'other-proof'
        protected.mkdir()
        header = protected / 'saved.h'
        header.write_text('protected proof input\n')
        alias = self.root / 'alias'
        alias.symlink_to(protected, target_is_directory=True)
        self.source.write_text('void f(void) {}\n')
        for destination in (alias, alias / 'include'):
            with self.subTest(destination=destination):
                with self.assertRaisesRegex(ValueError, 'destination uses a symlink'):
                    snapshot_headers(self.source, destination, self.includes)
                self.assertEqual(header.read_text(), 'protected proof input\n')
        self.assertFalse((protected / 'include').exists())

    def test_deleted_header_does_not_survive_reused_trial_folder(self):
        dependency = self.includes / 'dependency.h'
        dependency.write_text('value\n')
        self.snapshot('#include "dependency.h"\n')
        dependency.unlink()
        receipt = self.snapshot('#include "dependency.h"\n')
        self.assertEqual(receipt['selection'], 'all project headers')
        self.assertFalse((self.output / 'dependency.h').exists())

    def test_generated_local_snapshot_is_not_a_live_dependency(self):
        private = self.root / 'private.h'
        private.write_text('before\n')
        receipt = self.snapshot('#include "private.h"\n')
        private.unlink()
        receipt = self.snapshot('#include "private.h"\n')
        self.assertNotIn('private.h', receipt['source_bundle']['source_local_headers'])
        self.assertFalse((self.bundle(receipt) / 'private.h').exists())

    def test_project_snapshot_is_independent_of_later_live_changes(self):
        dependency = self.includes / 'dependency.h'
        dependency.write_text('before\n')
        receipt = self.snapshot('#include "dependency.h"\n')
        dependency.write_text('after\n')
        self.assertEqual((self.output / 'dependency.h').read_text(), 'before\n')
        verify_snapshot_inputs(receipt, self.output)
        self.assertEqual(json.loads((self.output.parent / 'header-snapshot.json').read_text()), receipt)

    def test_private_source_is_retained_and_original_mutations_rejected(self):
        private = self.root / 'private.h'
        private.write_text('before\n')
        receipt = self.snapshot('#include "private.h"\n')
        saved = self.bundle(receipt) / 'private.h'
        private.write_text('after\n')
        self.assertEqual(saved.read_text(), 'before\n')
        with self.assertRaisesRegex(ValueError, 'changed during compilation'):
            verify_snapshot_inputs(receipt, self.output)
        private.unlink()
        with self.assertRaisesRegex(ValueError, 'not a regular file'):
            verify_snapshot_inputs(receipt, self.output)

    def test_retained_source_local_and_project_mutations_are_rejected(self):
        (self.root / 'private.h').write_text('#include "unused.h"\n')
        for target in ('source', 'private', 'project'):
            with self.subTest(target=target):
                receipt = self.snapshot('#include "private.h"\n')
                path = {'source': retained_source(receipt, self.output),
                        'private': self.bundle(receipt) / 'private.h',
                        'project': self.output / 'unused.h'}[target]
                path.write_text('changed\n')
                with self.assertRaisesRegex(ValueError, 'changed during compilation'):
                    verify_snapshot_inputs(receipt, self.output)

    def test_original_source_mutation_is_rejected(self):
        receipt = self.snapshot('void f(void) {}\n')
        self.source.write_text('void other(void) {}\n')
        with self.assertRaisesRegex(ValueError, 'changed during compilation'):
            verify_snapshot_inputs(receipt, self.output)

    def test_actual_dependencies_handle_spaces_dollars_and_line_splices(self):
        (self.root / 'private space$#.h').write_text('#include "unused.h"\n')
        receipt = self.snapshot('#include "private space$#.h"\n')
        paths = [retained_source(receipt, self.output), self.bundle(receipt) / 'private space$#.h',
                 self.output / 'unused.h']
        result = self.dependencies(receipt, paths)
        self.assertIn('source-inputs/private space$#.h', result)
        self.assertIn('include/unused.h', result)

    def test_actual_unretained_macro_dependency_and_missing_source_fail(self):
        receipt = self.snapshot('#include UNKNOWN\n')
        for paths in [[retained_source(receipt, self.output), self.includes / 'unused.h'],
                      [self.output / 'unused.h']]:
            with self.subTest(paths=paths):
                with self.assertRaisesRegex(ValueError, 'outside the retained snapshot'):
                    self.dependencies(receipt, paths)

    def test_comments_strings_and_line_splicing_do_not_hide_include(self):
        (self.includes / 'dependency.h').write_text('value\n')
        receipt = self.snapshot('char *s="/*";\n/* #include "unused.h" */\n'
                                '#inc\\\nlude "dependency.h" // tail\nchar *t="*/";\n')
        self.assertEqual(set(receipt['headers']), {'dependency.h'})
