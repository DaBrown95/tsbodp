"""The old backend must retain verified independent source and native locks."""
import copy
import hashlib
import json
import os
from pathlib import Path
import shutil
import stat
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from setup_old import provision
from toolchain import (OLD_BUILD, OLD_PIN, OLD_PROFILE, PROFILE, agbcc_old_source_files,
                       load_profile, sha, verify_agbcc_old_source, verify_native)


class OldAgbccProvisionTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.repository = self.root / 'toolchains/agbcc'
        self.source = self.repository / 'gcc'
        self.source.mkdir(parents=True)
        (self.root / 'config').mkdir()
        self.git('init', '-q')
        self.git('config', 'commit.gpgsign', 'false')
        for name, data, mode in [('Makefile', b'old: main.c\n', 0o644),
                                 ('main.c', b'int compiler_source;\n', 0o644),
                                 ('config/helper', b'#!/bin/sh\nexit 0\n', 0o755)]:
            path = self.source / name
            path.parent.mkdir(exist_ok=True)
            path.write_bytes(data)
            path.chmod(mode)
        self.commit()
        self.native_name = (OLD_BUILD / 'old_agbcc').as_posix()
        self.pins = {'compiler': {'source_commit': self.git('rev-parse', 'HEAD').strip(),
                                 'source_subdirectory': 'gcc',
                                 'build_directory': OLD_BUILD.as_posix(),
                                 'build_options': ['old', '-j1'],
                                 'tracked_source_file_count': 3,
                                 'tracked_source_tree_sha256': self.identity()},
                     'native_tool_sha256': {self.native_name: hashlib.sha256(b'reference native').hexdigest()},
                     'host_clang': 'reference host'}
        self.pin_path = self.root / OLD_PIN
        self.write_pin()
        self.commands = []
        # These normal/generated outputs must never enter the copied source set.
        (self.source / 'agbcc').write_bytes(b'current backend remains unchanged')
        (self.source / 'main.o').write_bytes(b'untracked generated output')

    def git(self, *args):
        return subprocess.check_output(['git', '-C', self.repository, *args], text=True)

    def commit(self):
        self.git('add', 'gcc')
        self.git('-c', 'user.name=Fixture', '-c', 'user.email=fixture@example.invalid',
                 'commit', '-qm', 'Fixture tracked compiler source')

    def identity(self):
        digest = hashlib.sha256()
        for name in sorted(('Makefile', 'main.c', 'config/helper')):
            path = self.source / name
            mode = b'100755' if name == 'config/helper' else b'100644'
            digest.update(name.encode() + b'\0' + mode + b'\0' + bytes.fromhex(sha(path)))
        return digest.hexdigest()

    def write_pin(self):
        self.pin_path.write_text(json.dumps(self.pins))

    def runner(self, command, *, cwd):
        self.commands.append(([str(x) for x in command], cwd))
        self.assertEqual(command, ['make', 'old', '-j1'])
        self.assertEqual(cwd, self.root / OLD_BUILD)
        self.assertFalse((cwd / 'agbcc').exists())
        self.assertFalse((cwd / 'main.o').exists())
        (cwd / 'main.o').write_bytes(b'fresh generated object')
        binary = self.root / self.native_name
        binary.write_bytes(b'fresh native')
        binary.chmod(0o755)

    def copied_source(self):
        build = self.root / OLD_BUILD
        build.mkdir(parents=True)
        for name in ('Makefile', 'main.c', 'config/helper'):
            destination = build / name
            destination.parent.mkdir(exist_ok=True)
            shutil.copyfile(self.source / name, destination)
            destination.chmod(stat.S_IMODE((self.source / name).stat().st_mode))
        return build

    def test_fresh_build_uses_only_tracked_copies_and_separate_profile(self):
        public_before = self.pin_path.read_bytes()
        current_before = (self.source / 'agbcc').read_bytes()
        self.assertTrue(provision(self.root, self.pins, 'fresh host', self.runner))
        self.assertEqual(self.pin_path.read_bytes(), public_before)
        self.assertEqual((self.source / 'agbcc').read_bytes(), current_before)
        self.assertEqual(self.git('status', '--porcelain', '--untracked-files=no'), '')
        self.assertFalse((self.root / PROFILE).exists())
        lock, local = load_profile(self.root, OLD_PIN, OLD_PROFILE)
        self.assertEqual(local, OLD_PROFILE)
        self.assertEqual(lock['compiler'], self.pins['compiler'])
        verify_native(self.root, lock, 'fresh host')
        inputs = verify_agbcc_old_source(self.root, lock)
        self.assertEqual(len(inputs), 6)
        for original, copied in zip(inputs[::2], inputs[1::2]):
            self.assertNotEqual(original.stat().st_ino, copied.stat().st_ino)
            self.assertEqual(original.read_bytes(), copied.read_bytes())
        self.assertFalse(provision(self.root, self.pins, 'fresh host', self.runner))
        self.assertEqual(len(self.commands), 1)

    def test_known_public_binary_is_verified_without_enrollment_or_writes(self):
        build = self.copied_source()
        binary = build / 'old_agbcc'
        binary.write_bytes(b'reference native')
        before = {p: (p.read_bytes(), p.stat().st_mtime_ns) for p in build.rglob('*') if p.is_file()}
        self.assertFalse(provision(self.root, self.pins, 'reference host', self.runner))
        self.assertEqual({p: (p.read_bytes(), p.stat().st_mtime_ns) for p in before}, before)
        self.assertFalse((self.root / OLD_PROFILE).exists())
        self.assertEqual(self.commands, [])

    def test_unknown_existing_binary_is_never_adopted(self):
        build = self.copied_source()
        (build / 'old_agbcc').write_bytes(b'unknown native')
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            provision(self.root, self.pins, 'reference host', self.runner)
        self.assertFalse((self.root / OLD_PROFILE).exists())
        self.assertEqual(self.commands, [])

    def test_incomplete_build_is_preserved(self):
        build = self.root / OLD_BUILD
        build.mkdir()
        (build / 'old.o').write_bytes(b'held incomplete build')
        with self.assertRaisesRegex(RuntimeError, 'Incomplete'):
            provision(self.root, self.pins, 'fresh host', self.runner)
        self.assertEqual((build / 'old.o').read_bytes(), b'held incomplete build')
        self.assertEqual(self.commands, [])

    def test_interrupted_profile_temporary_is_not_overwritten(self):
        temporary = (self.root / OLD_PROFILE).with_suffix('.tmp')
        temporary.write_bytes(b'held interrupted profile')
        with self.assertRaises(FileExistsError):
            provision(self.root, self.pins, 'fresh host', self.runner)
        self.assertEqual(temporary.read_bytes(), b'held interrupted profile')
        self.assertFalse((self.root / OLD_PROFILE).exists())

    def test_wrong_commit_and_public_tree_identity_reject_before_copy(self):
        for field, value in [('source_commit', '0' * 40),
                             ('tracked_source_tree_sha256', '0' * 64),
                             ('tracked_source_file_count', 4),
                             ('source_subdirectory', '../gcc'),
                             ('build_directory', 'toolchains/agbcc/gcc')]:
            changed = copy.deepcopy(self.pins)
            changed['compiler'][field] = value
            with self.subTest(field=field), self.assertRaises(RuntimeError):
                provision(self.root, changed, 'fresh host', self.runner)
            self.assertFalse((self.root / OLD_BUILD).exists())
        self.assertEqual(self.commands, [])

    def test_parallel_bootstrap_recipe_rejects_before_copy_or_native_enrollment(self):
        # A warmed source tree hides missing genrtl.h ordering in upstream's
        # parallel recipe. Even a later -j4 must not override the serial pin.
        for options in (['old', '-j4'], ['old', '-j1', '-j4'], ['old'],
                        ['old', '-j1', 'MAKEFLAGS=-j4']):
            changed = copy.deepcopy(self.pins)
            changed['compiler']['build_options'] = options
            with self.subTest(options=options), self.assertRaisesRegex(RuntimeError, 'serial recipe'):
                provision(self.root, changed, 'fresh host', self.runner)
            self.assertFalse((self.root / OLD_BUILD).exists())
            self.assertFalse((self.root / OLD_PROFILE).exists())
        self.assertEqual(self.commands, [])

    def test_live_tracked_source_drift_rejects_even_if_git_ignores_worktree(self):
        # Byte/blob verification must still work when Git's status can be fooled
        # by assume-unchanged rather than trusting only the clean status string.
        self.git('update-index', '--assume-unchanged', 'gcc/main.c')
        (self.source / 'main.c').write_bytes(b'changed live source')
        self.assertEqual(self.git('status', '--porcelain', '--untracked-files=no'), '')
        with self.assertRaisesRegex(RuntimeError, 'Git blob'):
            provision(self.root, self.pins, 'fresh host', self.runner)
        self.assertFalse((self.root / OLD_BUILD).exists())

    def test_tracked_modes_and_symlinks_cannot_be_substituted(self):
        self.git('config', 'core.filemode', 'false')
        (self.source / 'config/helper').chmod(0o644)
        with self.assertRaisesRegex(RuntimeError, 'Git mode'):
            agbcc_old_source_files(self.root, self.pins)
        (self.source / 'config/helper').chmod(0o755)
        (self.source / 'main.c').unlink()
        (self.source / 'main.c').symlink_to('Makefile')
        self.git('add', 'gcc/main.c')
        self.git('-c', 'user.name=Fixture', '-c', 'user.email=fixture@example.invalid',
                 'commit', '-qm', 'Fixture symlink must reject')
        self.pins['compiler']['source_commit'] = self.git('rev-parse', 'HEAD').strip()
        with self.assertRaisesRegex(RuntimeError, 'tracked source entry'):
            agbcc_old_source_files(self.root, self.pins)

    def test_tree_path_escape_rejects_before_source_access(self):
        original = subprocess.check_output

        def response(command, **kwargs):
            if 'ls-tree' in command:
                return b'100644 blob ' + b'0' * 40 + b'\tgcc/../../outside\0'
            return original(command, **kwargs)

        with patch('toolchain.subprocess.check_output', side_effect=response):
            with self.assertRaisesRegex(RuntimeError, 'tracked source entry'):
                agbcc_old_source_files(self.root, self.pins)

    def test_existing_native_does_not_hide_copy_drift_or_live_inode_alias(self):
        build = self.copied_source()
        (build / 'old_agbcc').write_bytes(b'reference native')
        copied = build / 'main.c'
        copied.write_bytes(b'changed copied source')
        with self.assertRaisesRegex(RuntimeError, 'isolated source copy'):
            provision(self.root, self.pins, 'reference host', self.runner)
        copied.unlink()
        os.link(self.source / 'main.c', copied)
        with self.assertRaisesRegex(RuntimeError, 'aliases the live source'):
            provision(self.root, self.pins, 'reference host', self.runner)
        self.assertEqual(self.commands, [])

    def test_copied_directory_symlink_and_profile_symlink_reject(self):
        build = self.copied_source()
        (build / 'old_agbcc').write_bytes(b'reference native')
        (build / 'config/helper').unlink()
        (build / 'config').rmdir()
        (build / 'config').symlink_to(self.source / 'config')
        with self.assertRaisesRegex(RuntimeError, 'symbolic link'):
            provision(self.root, self.pins, 'reference host', self.runner)
        (self.root / OLD_PROFILE).symlink_to(self.pin_path)
        with self.assertRaisesRegex(RuntimeError, 'profile must not'):
            provision(self.root, self.pins, 'reference host', self.runner)

    def test_after_build_copy_drift_prevents_profile_enrollment(self):
        def changed(command, *, cwd):
            self.runner(command, cwd=cwd)
            (cwd / 'main.c').write_bytes(b'mutated during build')

        with self.assertRaisesRegex(RuntimeError, 'isolated source copy'):
            provision(self.root, self.pins, 'fresh host', changed)
        self.assertFalse((self.root / OLD_PROFILE).exists())

    def test_after_build_upstream_drift_prevents_profile_enrollment(self):
        def changed(command, *, cwd):
            self.runner(command, cwd=cwd)
            (self.source / 'main.c').write_bytes(b'mutated upstream during build')

        with self.assertRaisesRegex(RuntimeError, 'tracked changes'):
            provision(self.root, self.pins, 'fresh host', changed)
        self.assertFalse((self.root / OLD_PROFILE).exists())

    def test_failed_build_keeps_raw_outputs_without_profile(self):
        def failed(command, *, cwd):
            self.runner(command, cwd=cwd)
            raise RuntimeError('fixture build failed')

        with self.assertRaisesRegex(RuntimeError, 'fixture build failed'):
            provision(self.root, self.pins, 'fresh host', failed)
        self.assertTrue((self.root / OLD_BUILD / 'main.o').exists())
        self.assertFalse((self.root / OLD_PROFILE).exists())
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            provision(self.root, self.pins, 'reference host', self.runner)

    def test_stale_profile_native_host_and_missing_copy_reject(self):
        provision(self.root, self.pins, 'fresh host', self.runner)
        with self.assertRaisesRegex(RuntimeError, 'preprocessor'):
            provision(self.root, self.pins, 'changed host', self.runner)
        binary = self.root / self.native_name
        original = binary.read_bytes()
        binary.write_bytes(b'changed native')
        with self.assertRaisesRegex(RuntimeError, 'Native tool'):
            provision(self.root, self.pins, 'fresh host', self.runner)
        binary.write_bytes(original)
        copied = self.root / OLD_BUILD / 'main.c'
        copied.unlink()
        with self.assertRaises(FileNotFoundError):
            provision(self.root, self.pins, 'fresh host', self.runner)
        shutil.copyfile(self.source / 'main.c', copied)
        self.pin_path.write_text(json.dumps({**self.pins, 'scope': 'changed pin'}))
        with self.assertRaisesRegex(RuntimeError, 'stale'):
            provision(self.root, self.pins, 'fresh host', self.runner)

    def test_profile_cannot_drop_native_pin_or_reenroll_its_fingerprint(self):
        provision(self.root, self.pins, 'fresh host', self.runner)
        profile_path = self.root / OLD_PROFILE
        profile = json.loads(profile_path.read_text())
        profile['native_tool_sha256'] = {}
        profile_path.write_text(json.dumps(profile))
        before = profile_path.read_bytes()
        with self.assertRaisesRegex(RuntimeError, 'every required'):
            provision(self.root, self.pins, 'fresh host', self.runner)
        self.assertEqual(profile_path.read_bytes(), before)
        self.assertEqual(len(self.commands), 1)


if __name__ == '__main__':
    unittest.main()
