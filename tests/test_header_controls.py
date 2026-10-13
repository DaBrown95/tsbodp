"""A hardware control edits a retained include, never an unrelated live file."""
import hashlib
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from header_snapshots import snapshot_headers, retained_source
try:
    import pilot
    from pilot import compile_function
except ModuleNotFoundError as error:
    if error.name != 'elftools':
        raise
    compile_function = None


@unittest.skipUnless(compile_function, 'Compiler module requires the analysis environment')
class HeaderControlTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.folder = Path(temporary.name).resolve()
        self.source = self.folder / 'source.c'
        self.source.write_text('#include "bios.h"\nvoid f(void) {}\n')
        self.project = self.folder / 'project'
        self.project.mkdir()
        (self.project / 'bios.h').write_text('original\n')

    def snapshot(self, source, destination, include_root):
        return snapshot_headers(source, destination, self.project)

    def test_unknown_and_traversing_header_controls_fail_before_compilation(self):
        for name in ('unrelated.h', '../bios.h', '/private/bios.h'):
            with self.subTest(name=name), patch('pilot.snapshot_headers', self.snapshot), patch('pilot.run') as run:
                with self.assertRaisesRegex(ValueError, 'outside the source include closure'):
                    compile_function({}, self.source, self.folder / name.replace('/', '_'), [],
                                     header_overrides={name: 'changed\n'})
                run.assert_not_called()

    def test_control_snapshot_records_the_changed_header_hash(self):
        # Stop at the preprocessor: the proof input must already be fully retained.
        output = self.folder / 'control'
        function = {'name': 'f', 'rom_offset': 0, 'size': 4}
        with patch('pilot.snapshot_headers', self.snapshot), patch('pilot.run', side_effect=RuntimeError('stop')):
            with self.assertRaisesRegex(RuntimeError, 'stop'):
                compile_function(function, self.source, output, ['-O2'], copies=[],
                                 header_overrides={'bios.h': 'changed\n'})
        self.assertEqual((output / 'include/bios.h').read_text(), 'changed\n')
        receipt = json.loads((output / 'header-snapshot.json').read_text())
        self.assertEqual(receipt['headers']['bios.h'], hashlib.sha256(b'changed\n').hexdigest())

    def private_source(self):
        self.source.write_text('#include "private.h"\nvoid f(void) {}\n')
        (self.folder / 'private.h').write_text('#include "bios.h"\n')

    def preprocessing_run(self, output, mutation):
        def run(command, commands):
            commands.append([str(value) for value in command])
            if '-E' in command:
                receipt = json.loads((output / 'header-snapshot.json').read_text())
                source = retained_source(receipt, output / 'include')
                inputs = [source, *(source.parent / name for name in receipt['source_bundle']['source_local_headers']),
                          *(output / 'include' / name for name in receipt['headers'])]
                Path(command[command.index('-o') + 1]).write_text('void f(void) {}\n')
                Path(command[command.index('-MF') + 1]).write_text(
                    'snapshot: ' + ' '.join(str(path) for path in inputs) + '\n')
                mutation('preprocess', source)
            else:
                mutation('compile', retained_source(
                    json.loads((output / 'header-snapshot.json').read_text()), output / 'include'))
        return run

    def test_original_and_retained_local_mutations_stop_before_compiler(self):
        self.private_source()
        for retained in (False, True):
            with self.subTest(retained=retained):
                (self.folder / 'private.h').write_text('#include "bios.h"\n')
                output = self.folder / ('saved' if retained else 'original')
                def mutation(phase, source):
                    target = source.parent / 'private.h' if retained else self.folder / 'private.h'
                    target.write_text('changed\n')
                with patch('pilot.snapshot_headers', self.snapshot), patch(
                        'pilot.run', side_effect=self.preprocessing_run(output, mutation)) as run:
                    with self.assertRaisesRegex(ValueError, 'changed during compilation'):
                        compile_function({'name': 'f', 'rom_offset': 0, 'size': 4}, self.source,
                                         output, ['-O2'], copies=[])
                    self.assertEqual(run.call_count, 1)

    def test_local_mutation_during_compiler_stops_before_assembly(self):
        self.private_source()
        output = self.folder / 'compiler-change'
        def mutation(phase, source):
            if phase == 'compile':
                (self.folder / 'private.h').write_text('changed\n')
        with patch('pilot.snapshot_headers', self.snapshot), patch(
                'pilot.run', side_effect=self.preprocessing_run(output, mutation)) as run:
            with self.assertRaisesRegex(ValueError, 'changed during compilation'):
                compile_function({'name': 'f', 'rom_offset': 0, 'size': 4}, self.source,
                                 output, ['-O2'], copies=[])
            self.assertEqual(run.call_count, 2)

    def test_macro_dependency_on_live_header_stops_before_compiler(self):
        self.private_source()
        output = self.folder / 'macro-escape'
        def mutation(phase, source):
            if phase == 'preprocess':
                with (output / 'preprocessor.d').open('a') as stream:
                    stream.write(str(self.project / 'bios.h') + '\n')
        with patch('pilot.snapshot_headers', self.snapshot), patch(
                'pilot.run', side_effect=self.preprocessing_run(output, mutation)) as run:
            with self.assertRaisesRegex(ValueError, 'outside the retained snapshot'):
                compile_function({'name': 'f', 'rom_offset': 0, 'size': 4}, self.source,
                                 output, ['-O2'], copies=[])
            self.assertEqual(run.call_count, 1)

    @unittest.skipUnless(shutil.which('xcrun'), 'Host preprocessor is not installed')
    def test_real_preprocessor_absolute_macro_escape_is_rejected(self):
        private = self.folder / 'private.h'
        private.write_text('#define VALUE 7\n')
        self.source.write_text('#define HEADER "' + str(private) + '"\n'
                               '#include HEADER\nunsigned f(void) { return VALUE; }\n')
        with patch('pilot.snapshot_headers', self.snapshot), patch('pilot.run', wraps=pilot.run) as run:
            with self.assertRaisesRegex(ValueError, 'outside the retained snapshot'):
                compile_function({'name': 'f', 'rom_offset': 0, 'size': 4}, self.source,
                                 self.folder / 'real-escape', ['-O2'], copies=[])
            self.assertEqual(run.call_count, 1)

    @unittest.skipUnless(shutil.which('xcrun') and
                         (Path(__file__).resolve().parents[1] / 'toolchains/agbcc/gcc/agbcc').is_file(),
                         'Native source fixture requires the provisioned compiler')
    def test_macro_private_header_change_reaches_native_output(self):
        results = []
        for value in (7, 8):
            source_root = self.folder / str(value)
            source_root.mkdir()
            source = source_root / 'source.c'
            source.write_text('#define HEADER "private.h"\n#include HEADER\n'
                              'unsigned f(void) { return VALUE; }\n')
            (source_root / 'private.h').write_text('#define VALUE ' + str(value) + '\n')
            output = source_root / 'proof'
            with patch('pilot.snapshot_headers', self.snapshot):
                data, _ = compile_function({'name': 'f', 'rom_offset': 0, 'size': 4},
                                           source, output, ['-O2'], copies=[])
            receipt = json.loads((output / 'header-snapshot.json').read_text())
            self.assertEqual(receipt['selection'], 'all project headers')
            self.assertEqual(receipt['preprocessor_dependencies'],
                             ['source-inputs/private.h', 'source-inputs/source.c'])
            results.append(data)
        self.assertNotEqual(*results)
