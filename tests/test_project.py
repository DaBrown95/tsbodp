"""Negative controls for the identity and all-byte comparison gates."""

import hashlib
import importlib.util
from pathlib import Path
import unittest


spec = importlib.util.spec_from_file_location(
    "project", Path(__file__).resolve().parents[1] / "tools/project.py")
project = importlib.util.module_from_spec(spec)
spec.loader.exec_module(project)


class IdentityTests(unittest.TestCase):
    def setUp(self):
        data = bytearray(512)
        data[0xAC:0xB0] = b"ASIE"
        data[0xB2] = 0x96
        data[0xBD] = (-sum(data[0xA0:0xBD]) - 0x19) & 0xFF
        self.data = bytes(data)
        self.target = {"id": "synthetic", "size": len(data),
                       "sha1": hashlib.sha1(data).hexdigest(),
                       "game_code": "ASIE", "revision": 0}

    def test_valid_synthetic_identity(self):
        self.assertTrue(project.inspect_rom(self.data, self.target)["accepted"])

    def test_mutation_outside_header_rejected(self):
        data = bytearray(self.data)
        data[-1] ^= 1
        result = project.inspect_rom(bytes(data), self.target)
        self.assertFalse(result["accepted"])
        self.assertTrue(result["checks"]["header_checksum"])
        self.assertFalse(result["checks"]["catalogue_sha1"])

    def test_bad_checksum_rejected_even_with_matching_hash(self):
        data = bytearray(self.data)
        data[0xBD] ^= 1
        target = dict(self.target, sha1=hashlib.sha1(data).hexdigest())
        self.assertFalse(project.inspect_rom(bytes(data), target)["accepted"])

    def test_revision_rejected_even_with_valid_checksum_and_hash(self):
        data = bytearray(self.data)
        data[0xBC] = 1
        data[0xBD] = (-sum(data[0xA0:0xBD]) - 0x19) & 0xFF
        target = dict(self.target, sha1=hashlib.sha1(data).hexdigest())
        result = project.inspect_rom(bytes(data), target)
        self.assertFalse(result["accepted"])
        self.assertFalse(result["checks"]["revision"])

    def test_truncated_header_rejected(self):
        self.assertFalse(project.inspect_rom(b"ASIE", self.target)["accepted"])

    def test_pinned_sha256_is_enforced(self):
        target = dict(self.target, sha256="0" * 64)
        result = project.inspect_rom(self.data, target)
        self.assertTrue(result["checks"]["catalogue_sha1"])
        self.assertFalse(result["accepted"])
        self.assertFalse(result["checks"]["sha256"])


class ComparisonTests(unittest.TestCase):
    def test_equal_bytes_do_not_claim_source_recovery(self):
        result = project.compare_bytes(b"abc", b"abc")
        self.assertTrue(result["identical"])
        self.assertFalse(result["source_reconstruction_verified"])

    def test_every_offset_checked(self):
        reference = bytes(512)
        for offset in range(len(reference)):
            candidate = bytearray(reference)
            candidate[offset] = 1
            result = project.compare_bytes(reference, bytes(candidate))
            self.assertFalse(result["identical"])
            self.assertEqual(result["differing_bytes_including_missing_or_extra"], 1)
            self.assertEqual(result["first_differences"][0]["offset"], offset)

    def test_truncation_and_extra_padding_rejected(self):
        for candidate in (b"ab", b"abc\0"):
            result = project.compare_bytes(b"abc", candidate)
            self.assertFalse(result["identical"])
            self.assertEqual(result["differing_bytes_including_missing_or_extra"], 1)


if __name__ == "__main__":
    unittest.main()
