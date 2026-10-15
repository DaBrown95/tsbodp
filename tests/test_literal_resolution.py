"""Explicit literal addresses must not turn data roots into guessed names/CFG."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import resolve_literals as literals

BASE = literals.BASE


def identity(data):
    return {'id': 'us-eu', 'rom_path': 'baseroms/test.gba', 'size': len(data),
            'sha1': hashlib.sha1(data).hexdigest(),
            'sha256': hashlib.sha256(data).hexdigest(),
            'game_code': 'ASIE', 'revision': 0}


def reference():
    data = bytearray(512)
    # Two sites at +2 mod4 exercise Thumb alignment; their literal values differ.
    struct.pack_into('<H', data, 2, 0x4801)
    struct.pack_into('<H', data, 6, 0x4a01)
    struct.pack_into('<II', data, 8, 0x03005a00, 0x03004350)
    data[0xac:0xb0] = b'ASIE'
    data[0xb2] = 0x96
    data[0xbd] = (-sum(data[0xa0:0xbd]) - 0x19) & 255
    return bytes(data)


class LiteralTests(unittest.TestCase):
    def test_thumb_plus_two_aligns_pc_before_displacement(self):
        row = literals.resolve_word_literal(reference(), BASE+2)
        self.assertEqual(row['effective_pc'], BASE+4)
        self.assertEqual(row['literal_address'], BASE+8)
        self.assertEqual(row['instruction_bytes'], '0148')
        self.assertEqual(row['literal_bytes'], '005a0003')
        self.assertEqual(row['value'], 0x03005a00)
        self.assertEqual(row['destination_register'], 'r0')

    def test_arm_negative_immediate_and_condition_are_preserved(self):
        data = bytearray(16)
        struct.pack_into('<I', data, 4, 0x03004350)
        struct.pack_into('<I', data, 8, 0x051f100c)  # LDREQ r1,[PC,#-12].
        row = literals.resolve_word_literal(data, BASE+8, 'ARM')
        self.assertEqual(row['effective_pc'], BASE+16)
        self.assertEqual(row['displacement'], -12)
        self.assertEqual(row['literal_address'], BASE+4)
        self.assertEqual(row['value'], 0x03004350)
        self.assertEqual(row['ARM_condition_bits'], 0)

    def test_pc_destination_is_not_a_claim_of_transfer_execution(self):
        data = struct.pack('<III', 0xe59ff000, 0, 0x08000001)
        row = literals.resolve_word_literal(data, BASE, 'ARM')
        self.assertEqual(row['destination_register'], 'r15')
        self.assertEqual(row['value'], 0x08000001)

    def test_nonliteral_thumb_and_thumb2_are_rejected(self):
        for opcode in (0x5800, 0x6800, 0x2000, 0xf8df):
            with self.subTest(opcode=opcode), self.assertRaisesRegex(ValueError, 'Not an ARM7'):
                literals.resolve_word_literal(struct.pack('<H', opcode)+bytes(16), BASE)

    def test_arm_register_offsets_writeback_postindex_byte_and_store_reject(self):
        for opcode in (0xe79f0000, 0xe5bf0000, 0xe49f0000, 0xe5df0000,
                       0xe58f0000, 0xf59f0000, 0xe5900000, 0xe1df00b0):
            with self.subTest(opcode=hex(opcode)), self.assertRaisesRegex(ValueError, 'Not an ARM7'):
                literals.resolve_word_literal(struct.pack('<I', opcode)+bytes(16), BASE, 'ARM')

    def test_unaligned_arm_word_rotation_is_not_guessed(self):
        with self.assertRaisesRegex(ValueError, 'Unaligned'):
            literals.resolve_word_literal(struct.pack('<I', 0xe59f0001)+bytes(16), BASE, 'ARM')

    def test_truncated_instruction_and_pool_reject(self):
        for data, mode in ((b'\0', 'Thumb'), (b'\0'*3, 'ARM'),
                           (struct.pack('<H', 0x4802)+bytes(12), 'Thumb')):
            with self.subTest(mode=mode, size=len(data)), self.assertRaisesRegex(ValueError, 'outside'):
                literals.resolve_word_literal(data, BASE, mode)

    def test_pool_outside_span_rejects_before_word_read(self):
        with self.assertRaisesRegex(ValueError, 'outside'):
            literals.resolve_word_literal(struct.pack('<H', 0x48ff)+bytes(16), BASE)

    def test_misaligned_tagged_and_noninteger_sites_reject(self):
        for address in (BASE+1, -1, 1 << 32, True, 1.0):
            with self.subTest(address=address), self.assertRaises(ValueError):
                literals.resolve_word_literal(reference(), address)
        with self.assertRaises(ValueError):
            literals.resolve_word_literal(reference(), BASE+2, 'ARM')

    def test_pc_and_literal_arithmetic_never_wrap(self):
        cases = [(struct.pack('<H', 0x4800), 0xfffffffc, 'Thumb', 0xfffffffc),
                 (struct.pack('<I', 0xe59f0000), 0xfffffff8, 'ARM', 0xfffffff8),
                 (struct.pack('<I', 0xe59f0ffc)+bytes(12), 0xfffff000, 'ARM', 0xfffff000),
                 (struct.pack('<I', 0xe51f0010)+bytes(12), 0, 'ARM', 0)]
        for data, address, mode, base in cases:
            with self.subTest(address=address, mode=mode), self.assertRaisesRegex(ValueError, 'overflows'):
                literals.resolve_word_literal(data, address, mode, base)
        with self.assertRaisesRegex(ValueError, 'mapping exceeds'):
            literals.resolve_word_literal(bytes(8), 0xfffffffc, base=0xfffffffc)

    def test_fixed_identity_precedes_resolution(self):
        data = reference()
        target = dict(identity(data), sha256='0'*64)
        with patch.object(literals, 'resolve_word_literal', side_effect=AssertionError('resolved before audit')):
            with self.assertRaisesRegex(ValueError, 'identity audit'):
                literals.analyze_literals(data, target, [BASE+2])

    def test_report_distinguishes_actor_and_scene_and_never_reads_pointee(self):
        data = reference()
        manifest = {'target': 'us-eu', 'functions': [
            {'name': 'panel', 'symbols': {'g_actor': '0x03005a00', 'g_scene': '0x03004350'}}]}
        report = literals.analyze_literals(data, identity(data), [BASE+2, BASE+6],
                                          manifest=manifest, functions=['panel'])
        self.assertEqual([r['value'] for r in report['loads']], [0x03005a00, 0x03004350])
        self.assertEqual([r['provisional_symbol_bindings'][0]['symbol'] for r in report['loads']],
                         ['g_actor', 'g_scene'])
        self.assertFalse(report['control_flow_verified'])
        self.assertFalse(report['source_reconstruction_verified'])
        self.assertIn('caller-supplied', report['warnings'][0])

    def test_conflicting_names_are_flagged_without_changing_actual_word(self):
        manifest = {'functions': [{'name': 'a', 'symbols': {'g_root': '0x03005a00'}},
                                 {'name': 'b', 'symbols': {'g_root': '0x03004350'}}]}
        bindings, conflicts = literals.selected_bindings(manifest, ['a', 'b'])
        self.assertEqual(conflicts, [{'symbol': 'g_root', 'addresses': [0x03004350, 0x03005a00]}])
        self.assertTrue(all(b['name_has_conflicting_addresses'] for b in bindings))

    def test_names_never_clear_thumb_pointer_bits(self):
        data = bytearray(reference())
        struct.pack_into('<I', data, 8, BASE+1)
        manifest = {'target': 'us-eu', 'functions': [{'name': 'a', 'symbols': {'entry': hex(BASE)}}]}
        report = literals.analyze_literals(bytes(data), identity(data), [BASE+2],
                                          manifest=manifest, functions=['a'])
        self.assertEqual(report['loads'][0]['value'], BASE+1)
        self.assertEqual(report['loads'][0]['provisional_symbol_bindings'], [])

    def test_absent_ambiguous_repeated_or_wrong_target_selection_reject(self):
        for rows, selected in (([], ['missing']), ([{'name': 'a'}, {'name': 'a'}], ['a']),
                               ([{'name': 'a'}], ['a', 'a'])):
            with self.subTest(selected=selected), self.assertRaises(ValueError):
                literals.selected_bindings({'functions': rows}, selected)
        with self.assertRaisesRegex(ValueError, 'target differs'):
            literals.analyze_literals(reference(), identity(reference()), [BASE+2],
                                      manifest={'target': 'other'}, functions=['a'])

    def test_empty_duplicate_or_unbounded_site_list_reject(self):
        for addresses in ([], [BASE+2]*2, list(range(257))):
            with self.subTest(count=len(addresses)), self.assertRaisesRegex(ValueError, 'distinct explicit'):
                literals.analyze_literals(reference(), identity(reference()), addresses)


class CLITests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        (self.root/'config/targets').mkdir(parents=True)
        (self.root/'baseroms').mkdir()
        (self.root/'tools').mkdir()
        for name in ('resolve_literals.py', 'project.py'):
            (self.root/'tools'/name).write_bytes((Path(literals.__file__).parent/name).read_bytes())
        self.data = reference()
        (self.root/'baseroms/test.gba').write_bytes(self.data)
        (self.root/'config/targets/us-eu.json').write_text(json.dumps(identity(self.data)))
        (self.root/'reports/us-eu').mkdir(parents=True)
        self.audit = self.root/'reports/us-eu/audit.json'
        self.audit.write_text('previous audit must remain unchanged\n')
        self.output = self.root/'reports/new/literals.json'

    def run_cli(self, *args):
        with patch.object(literals, 'ROOT', self.root), contextlib.redirect_stdout(io.StringIO()), \
                contextlib.redirect_stderr(io.StringIO()):
            result = literals.main([*(hex(x) if isinstance(x, int) else x for x in args),
                                    '--output', str(self.output)])
        self.assertEqual(self.audit.read_text(), 'previous audit must remain unchanged\n')
        return result

    def test_successful_multiple_sites_pins_reference_and_helpers(self):
        self.assertEqual(self.run_cli(BASE+2, BASE+6), 0)
        report = json.loads(self.output.read_text())
        self.assertEqual(len(report['loads']), 2)
        self.assertEqual(report['reference_audit']['sha256'], identity(self.data)['sha256'])
        self.assertEqual(set(report['helper_sha256']), {'tools/resolve_literals.py', 'tools/project.py'})

    def test_wrong_reference_hash_writes_no_output(self):
        data = bytearray(self.data); data[-1] ^= 1
        (self.root/'baseroms/test.gba').write_bytes(data)
        self.assertEqual(self.run_cli(BASE+2), 1)
        self.assertFalse(self.output.parent.exists())

    def test_truncated_reference_writes_no_output(self):
        (self.root/'baseroms/test.gba').write_bytes(self.data[:100])
        self.assertEqual(self.run_cli(BASE+2), 1)
        self.assertFalse(self.output.exists())

    def test_second_invalid_instruction_prevents_partial_report(self):
        self.assertEqual(self.run_cli(BASE+2, BASE+16), 1)
        self.assertFalse(self.output.parent.exists())

    def test_existing_output_is_never_overwritten(self):
        self.output.parent.mkdir(); self.output.write_text('retained output\n')
        self.assertEqual(self.run_cli(BASE+2), 1)
        self.assertEqual(self.output.read_text(), 'retained output\n')

    def test_outside_reports_and_symlink_destination_reject(self):
        self.output = self.root/'outside.json'
        self.assertEqual(self.run_cli(BASE+2), 1)
        self.assertFalse(self.output.exists())
        outside = self.root/'outside'; outside.mkdir()
        (self.root/'reports/alias').symlink_to(outside, target_is_directory=True)
        self.output = self.root/'reports/alias/out.json'
        self.assertEqual(self.run_cli(BASE+2), 1)
        self.assertFalse((outside/'out.json').exists())

    def test_fixed_manifest_selection_is_optional_and_pinned(self):
        manifest = {'target': 'us-eu', 'functions': [
            {'name': 'a', 'symbols': {'g_actor': '0x03005a00'}}]}
        path = self.root/'config/build-us-eu.json'; path.write_text(json.dumps(manifest))
        self.assertEqual(self.run_cli(BASE+2, '--function', 'a'), 0)
        report = json.loads(self.output.read_text())
        self.assertEqual(report['manifest_sha256'], hashlib.sha256(path.read_bytes()).hexdigest())
        self.assertEqual(report['loads'][0]['provisional_symbol_bindings'][0]['symbol'], 'g_actor')


if __name__ == '__main__':
    unittest.main()
