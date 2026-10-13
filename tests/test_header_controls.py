"""A hardware control edits a retained include, never an unrelated live file."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
try:
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
        self.folder = Path(temporary.name)
        self.source = self.folder / 'source.c'
        self.source.write_text('void f(void) {}\n')

    def snapshot(self, source, destination, include_root):
        destination.mkdir(parents=True, exist_ok=True)
        (destination / 'bios.h').write_text('original\n')
        return {'selection': 'literal include closure',
                'headers': {'bios.h': hashlib.sha256(b'original\n').hexdigest()}}

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
