"""The full-build opt-in must reach the fresh pilot without becoming default."""
import contextlib
import io
from pathlib import Path
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
try:
    import build_rom
except ModuleNotFoundError as error:
    if error.name != 'elftools':
        raise
    build_rom = None


@unittest.skipUnless(build_rom, 'Build module requires the analysis environment')
class HeaderStoreEntrypointTests(unittest.TestCase):
    def pilot_command(self, arguments):
        # Stop on the first subprocess; no compiler, report or ROM write occurs.
        with patch.object(sys, 'argv', ['build_rom.py', *arguments]), patch.object(
                build_rom.subprocess, 'run', side_effect=RuntimeError('fresh pilot reached')) as run:
            with self.assertRaisesRegex(RuntimeError, 'fresh pilot reached'):
                build_rom.main()
        run.assert_called_once()
        self.assertTrue(run.call_args.kwargs['check'])
        return run.call_args.args[0]

    def test_default_full_build_keeps_ordinary_header_copies(self):
        command = self.pilot_command([])
        self.assertIn('--negative-control', command)
        self.assertNotIn('--share-project-headers', command)

    def test_explicit_full_build_flag_reaches_fresh_pilot(self):
        command = self.pilot_command(['--share-project-headers'])
        self.assertIn('--negative-control', command)
        self.assertEqual(command.count('--share-project-headers'), 1)

    def test_unknown_option_rejects_before_any_build_subprocess(self):
        with patch.object(sys, 'argv', ['build_rom.py', '--unknown-store-mode']), patch.object(
                build_rom.subprocess, 'run') as run, contextlib.redirect_stderr(io.StringIO()):
            with self.assertRaises(SystemExit) as raised:
                build_rom.main()
        self.assertEqual(raised.exception.code, 2)
        run.assert_not_called()


if __name__ == '__main__':
    unittest.main()
