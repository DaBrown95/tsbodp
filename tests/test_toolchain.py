"""Local host enrollment must preserve source pins and reject changed tools."""
import copy
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from setup import PENDING, pending_profile, verify_archive
from toolchain import PIN, PROFILE, ARM_PIN, ARM_PROFILE, load_profile, sha, validate_profile, verify_native


class ToolchainTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.names = ['toolchains/compiler', 'toolchains/as', 'toolchains/ld', 'toolchains/objcopy']
        for name in self.names:
            p = self.root / name
            p.parent.mkdir(exist_ok=True)
            p.write_bytes(name.encode())
        self.pins = {'compiler': {'source_commit': 'fixed-public-source'},
                     'native_tool_sha256': {name: sha(self.root / name) for name in self.names},
                     'host_clang': 'original host'}
        (self.root / PIN).parent.mkdir()
        (self.root / PIN).write_text(json.dumps(self.pins))
        self.profile = {'source_pin_sha256': sha(self.root / PIN),
                        'native_tool_sha256': dict(self.pins['native_tool_sha256']),
                        'host_clang': 'new host'}

    def test_original_profile_still_works_without_setup(self):
        lock, local = load_profile(self.root)
        self.assertIsNone(local)
        verify_native(self.root, lock, 'original host')

    def test_local_host_does_not_replace_public_source_pins(self):
        (self.root / PROFILE).write_text(json.dumps(self.profile))
        lock, local = load_profile(self.root)
        self.assertEqual(local, PROFILE)
        self.assertEqual(lock['compiler'], self.pins['compiler'])
        self.assertEqual(lock['host_clang'], 'new host')
        verify_native(self.root, lock, 'new host')

    def test_changed_source_pins_invalidate_local_profile(self):
        (self.root / PROFILE).write_text(json.dumps(self.profile))
        (self.root / PIN).write_text(json.dumps({**self.pins, 'compiler': {'source_commit': 'changed'}}))
        with self.assertRaises(RuntimeError):
            load_profile(self.root)

    def test_arm_profile_is_independent_and_cannot_replace_thumb_profile(self):
        (self.root / ARM_PIN).write_text(json.dumps(self.pins))
        arm = {**self.profile, 'source_pin_sha256': sha(self.root / ARM_PIN)}
        (self.root / ARM_PROFILE).write_text(json.dumps(arm))
        lock, local = load_profile(self.root, ARM_PIN, ARM_PROFILE)
        self.assertEqual(local, ARM_PROFILE)
        verify_native(self.root, lock, 'new host')
        thumb, local = load_profile(self.root)
        self.assertIsNone(local)
        verify_native(self.root, thumb, 'original host')
        (self.root / ARM_PIN).write_text(json.dumps({**self.pins, 'compiler': {'source_commit': 'changed'}}))
        with self.assertRaises(RuntimeError):
            load_profile(self.root, ARM_PIN, ARM_PROFILE)

    def test_every_native_tool_including_objcopy_is_checked(self):
        for name in self.names:
            p = self.root / name
            original = p.read_bytes()
            p.write_bytes(original + b'changed')
            with self.subTest(name=name), self.assertRaises(RuntimeError):
                verify_native(self.root, self.profile, 'new host')
            p.write_bytes(original)

    def test_changed_preprocessor_is_rejected(self):
        with self.assertRaises(RuntimeError):
            verify_native(self.root, self.profile, 'another host')

    def test_incomplete_or_invalid_profile_is_rejected(self):
        variants = [copy.deepcopy(self.profile) for _ in range(3)]
        del variants[0]['native_tool_sha256'][self.names[-1]]
        variants[1]['native_tool_sha256'][self.names[0]] = 'not a hash'
        variants[2]['host_clang'] = ''
        for profile in variants:
            with self.subTest(profile=profile), self.assertRaises(RuntimeError):
                validate_profile(profile, self.pins, sha(self.root / PIN))

    def test_corrupt_download_is_rejected_before_extraction(self):
        archive = self.root / 'archive'
        archive.write_bytes(b'public archive')
        expected = hashlib.sha256(archive.read_bytes()).hexdigest()
        verify_archive(archive, expected)
        archive.write_bytes(b'corrupt download')
        with self.assertRaises(RuntimeError):
            verify_archive(archive, expected)

    def test_completed_component_can_resume_after_later_setup_failure(self):
        name = self.names[0]
        (self.root / name).write_bytes(b'freshly built on this machine')
        pending = {**self.profile, 'native_tool_sha256': {name: sha(self.root / name)}}
        (self.root / PENDING).write_text(json.dumps(pending))
        resumed = pending_profile(self.root, self.pins, 'new host')
        verify_native(self.root, resumed, 'new host')
        self.assertEqual(resumed['compiler'], self.pins['compiler'])
        (self.root / name).write_bytes(b'changed after interrupted setup')
        with self.assertRaises(RuntimeError):
            pending_profile(self.root, self.pins, 'new host')

    def test_incomplete_setup_cannot_resume_on_changed_host(self):
        (self.root / PENDING).write_text(json.dumps({**self.profile, 'native_tool_sha256': {}}))
        with self.assertRaises(RuntimeError):
            pending_profile(self.root, self.pins, 'different host')
