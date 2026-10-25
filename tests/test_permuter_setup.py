"""Fail-closed boundaries for private search setup; no proprietary target fixtures."""
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import permuter_setup as p


class PermuterSetupTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        subprocess.run(['git', 'init', '-q', str(self.root)], check=True)
        (self.root / '.gitignore').write_text('analysis/\n')
        (self.root / 'analysis/permuter').mkdir(parents=True)
        (self.root / 'config').mkdir()
        (self.root / 'assets').mkdir()

    def test_private_output_rejects_traversal_symlink_and_tracked(self):
        for bad in ('src/leak.o', 'analysis/permuter/../leak.o', 'analysis/permuter'):
            with self.subTest(bad=bad), self.assertRaises(ValueError):
                p.private_path(bad, self.root)
        (self.root / 'analysis/permuter/link').symlink_to(self.root / 'config', target_is_directory=True)
        with self.assertRaisesRegex(ValueError, 'Symlink'):
            p.private_path('analysis/permuter/link/payload', self.root)
        tracked = self.root / 'analysis/permuter/tracked.o'
        tracked.write_text('synthetic')
        subprocess.run(['git', 'add', '-f', str(tracked)], cwd=self.root, check=True)
        with self.assertRaisesRegex(ValueError, 'tracked'):
            p.private_path(tracked, self.root)
        self.assertEqual(p.private_path('analysis/permuter/fresh', self.root), self.root / 'analysis/permuter/fresh')

    def test_unignored_output_rejected(self):
        (self.root / '.gitignore').write_text('')
        with self.assertRaisesRegex(ValueError, 'ignored'):
            p.private_path('analysis/permuter/fresh', self.root)

    def test_gate_requires_real_instructions_changed_control_and_both_flags(self):
        gate = {'status': 'PASS_MATCHED_THUMB_GATE', 'matched_score': 0, 'changed_control_score': 5,
                'full_bytes_identical': True, 'actual_instruction_rows': 15,
                'stack_differences': True, 'ign_branch_targets': False}
        file = self.root / 'gate.json'
        for key, value in [('actual_instruction_rows', 0), ('changed_control_score', 0),
                           ('full_bytes_identical', False), ('stack_differences', False),
                           ('ign_branch_targets', True), ('matched_score', 1)]:
            file.write_text(json.dumps({**gate, key: value}))
            with self.subTest(key=key), self.assertRaises(ValueError):
                p.checked_gate(file)
        file.write_text(json.dumps(gate));self.assertEqual(p.checked_gate(file), gate)

    def test_optional_host_profile_absence_keeps_public_pin(self):
        pin = self.root / 'config/public-profile.json'
        contents = {'native_tool_sha256': {'compiler': 'a' * 64}, 'host_clang': 'fixture'}
        pin.write_text(json.dumps(contents))
        selection = {'pin': Path('config/public-profile.json'), 'profile': Path('absent-host-profile.json')}
        profile, files = p.profile_context(selection, self.root)
        self.assertEqual(profile, contents)
        self.assertEqual(files, [pin])
        self.assertTrue(all(f.is_file() for f in files))
        # A present malformed optional profile must still be rejected.
        (self.root / selection['profile']).write_text('{}')
        with self.assertRaisesRegex(RuntimeError, 'stale'):
            p.profile_context(selection, self.root)

    def test_pin_drift_rejected(self):
        file = self.root / 'input.c';file.write_text('old')
        record = p.record(file, self.root)
        p.verify_records([record], self.root)
        file.write_text('new')
        with self.assertRaisesRegex(ValueError, 'Pinned'):
            p.verify_records([record], self.root)

    def row_fixture(self, row, copies=()):
        (self.root / 'assets/rom-inventory.json').write_text(json.dumps({'rows': [row]}))
        (self.root / 'config/ram-map-us-eu.json').write_text(json.dumps({'copies': copies, 'entries': []}))
        (self.root / 'config/build-us-eu.json').write_text(json.dumps({'functions': [], 'compiler_flags': ['-O2', '-mthumb-interwork']}))

    def test_copied_arm_cannot_be_mislabeled_thumb_or_rom(self):
        row = {'rom_offset': 0xB840, 'mode': 'ARM', 'runtime_addresses': [0x03002900],
               'decoded_instruction_bytes': 272, 'referenced_literal_bytes': 12}
        copy = {'name': 'frame_draw_iwram', 'rom_offset': 0xB840, 'ram_address': 0x03002900, 'size': 284}
        self.row_fixture(row, [copy])
        function = {'name': 'sorter', 'rom_offset': 0xB840, 'size': 284, 'mode': 'ARM',
                    'ram_address': 0x03002900, 'ram_copy': 'frame_draw_iwram', 'compiler_id': 'agbcc_arm'}
        p.validate_row_selection(function, self.root)
        with self.assertRaisesRegex(ValueError, 'Wrong mode'):
            p.validate_row_selection({**function, 'mode': 'Thumb', 'compiler_id': 'agbcc'}, self.root)
        wrong = {k:v for k,v in function.items() if k not in ('ram_address', 'ram_copy')}
        with self.assertRaisesRegex(ValueError, 'execution/copy'):
            p.validate_row_selection(wrong, self.root)
        with self.assertRaises(ValueError):
            p.validate_row_selection({**function, 'size': 280}, self.root)

    def test_valid_backend_wrong_row_assignment_rejected(self):
        self.row_fixture({'rom_offset': 0x49968, 'mode': 'Thumb', 'runtime_addresses': [0x08049968],
                          'decoded_instruction_bytes': 106, 'referenced_literal_bytes': 16})
        function = {'name': 'row', 'rom_offset': 0x49968, 'size': 124, 'mode': 'Thumb',
                    'compiler_id': 'gcc302', 'compiler_flags': ['-O2', '-mthumb']}
        p.validate_row_selection(function, self.root)
        with self.assertRaisesRegex(ValueError, 'Wrong compiler assignment'):
            p.validate_row_selection({**function, 'compiler_id': 'agbcc'}, self.root)

    @unittest.skipUnless((p.ROOT / p.UPSTREAM / 'perm_pycparser').exists(), 'optional local upstream checkout')
    def test_contract_keeps_gnu_register_asm_and_forbids_external_changes(self):
        base = 'extern int value; int helper(int); int f(int arg) { register int v asm("r8") = arg; return helper(v) + value; } asm(".align 2, 0");'
        job = {'function': {'name': 'f'}, 'source_contract': p.source_contract(base, 'f')}
        p.check_candidate(base, job)
        # A real body-only result temporary is permitted; no contract or asm mutation.
        p.check_candidate(base.replace('return helper(v) + value;', 'int result = helper(v) + value; return result;'), job)
        for changed in [base.replace('int helper(int)', 'short helper(int)'),
                        base.replace('extern int value', 'extern short value'),
                        base.replace('int f(int arg)', 'int f(short arg)'),
                        base.replace('asm("r8")', 'asm("r9")'),
                        base.replace('.align 2, 0', '.incbin "target.o"')]:
            with self.subTest(changed=changed), self.assertRaises(Exception):
                p.check_candidate(changed, job)
        payload = 'void f(void) {} asm(".incbin \\"target.o\\"");'
        payload_job = {'function': {'name': 'f'}, 'source_contract': p.source_contract(payload, 'f')}
        with self.assertRaisesRegex(ValueError, 'external payloads'):
            p.check_candidate(payload, payload_job)
        with self.assertRaises(ValueError):
            p.source_contract('#include "reference.bin"\nint f(void){return 0;}', 'f')
        with self.assertRaises(ValueError):
            p.source_contract('int f(void){return 0;} int hidden(void){return 1;}', 'f')

    def test_weights_exclude_contract_mutation_and_fake_use_passes(self):
        forbidden = ('perm_pad_var_decl', 'perm_randomize_function_type', 'perm_randomize_external_type',
                     'perm_randomize_internal_type', 'perm_mult_zero', 'perm_dummy_comma_expr',
                     'perm_add_self_assignment', 'perm_duplicate_assignment', 'perm_remove_ast')
        self.assertTrue(all(p.SAFE_WEIGHTS.get(k, 0) == 0 for k in forbidden))

    def test_row_resolver_rejects_stale_source_and_missing_private_header(self):
        folder = self.root / 'analysis/candidate';folder.mkdir()
        best = {'private_headers': ['private.h'], 'source_local_headers': [], 'evidence_state': 'retained-inputs-revalidated', 'comparison_extent_bytes': 4, 'header_overrides': {'private.h': {'path': 'analysis/candidate/private.h', 'sha256': '0'*64}}}
        for key, data in [('source', 'void f(void){}'), ('metadata', '{"name":"f","rom_offset":4,"size":4}'),
                          ('receipt', '{}'), ('assessment', '{}')]:
            file = folder / (key + ('.c' if key == 'source' else '.json'));file.write_text(data)
            best[key] = file.relative_to(self.root).as_posix();best[key + '_sha256'] = p.digest(file)
        normal = folder / 'normal';normal.mkdir()
        (normal / 'header-snapshot.json').write_text(json.dumps({'headers': {'private.h': '0'*64}}))
        (self.root / 'config/triage-us-eu.json').write_text(json.dumps({'rows': [{'name': 'sub_08000004', 'rom_offset':4, 'mode':'Thumb', 'best_candidate':best}]}))
        with self.assertRaisesRegex(ValueError, 'Restore the private header'):
            p.resolve_row('sub_08000004', self.root)
        (self.root / best['source']).write_text('void f(void){return;}')
        with self.assertRaisesRegex(ValueError, 'candidate changed'):
            p.resolve_row('sub_08000004', self.root)


if __name__ == '__main__':
    unittest.main()
