"""Guarded dispatches must be proven; corrupt tables must stay unresolved."""
import struct
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
try:
    from inventory_rom import Scanner, BASE
except ModuleNotFoundError:
    Scanner = None


@unittest.skipIf(Scanner is None, 'Capstone is needed for control-flow tests')
class TransferTests(unittest.TestCase):
    def run_scanner(self, data, mode='Thumb'):
        scanner = Scanner(data, [])
        scanner.seed(BASE, mode, 'startup')
        scanner.drain()
        return scanner, scanner.results[(BASE, mode)]

    def switch(self, targets=None):
        # CMP r0,1; BHI default; LSL index,2; LDR table; ADD; LDR; MOV pc.
        return (bytes.fromhex('01280dd8800002494018006887460000')
                + struct.pack('<III', BASE+20, *(targets or [BASE+28, BASE+30]))
                + bytes.fromhex('704770477047'))

    def test_guarded_switch_cases_belong_to_current_function(self):
        scanner, result = self.run_scanner(self.switch())
        self.assertEqual(len(scanner.entries), 1)
        self.assertTrue({BASE+28, BASE+30, BASE+32} <= set(result['instructions']))
        self.assertEqual(result['unresolved_transfers'], set())
        record = next(r for r in result['transfer_records'] if r['kind'] == 'bounded_switch')
        self.assertEqual(record['case_count'], 2)
        self.assertEqual(record['table_rom_offset'], 20)
        self.assertTrue(set(range(20, 28)) <= result['literals'])
        self.assertFalse(any(BASE+p in result['instructions'] for p in range(16, 28)))

    def test_odd_outside_and_self_referential_tables_rejected(self):
        for targets in ([BASE+29, BASE+30], [BASE+0x1000, BASE+30], [BASE+20, BASE+30]):
            with self.subTest(targets=targets):
                _, result = self.run_scanner(self.switch(targets))
                self.assertIn(BASE+12, result['unresolved_transfers'])
                self.assertFalse(any(r['kind'] == 'bounded_switch' for r in result['transfer_records']))

    def test_guard_must_bound_the_same_index(self):
        data = bytearray(self.switch()); data[1] = 0x2a  # CMP r2,1, while dispatch uses r0.
        _, result = self.run_scanner(data)
        self.assertIn(BASE+12, result['unresolved_transfers'])

    def test_guard_count_cannot_overrun_table_image(self):
        data = bytearray(self.switch()); data[0] = 255
        _, result = self.run_scanner(data)
        self.assertIn(BASE+12, result['unresolved_transfers'])

    def test_bls_plus_default_branch_switch(self):
        data = (bytes.fromhex('00b5012800d90de0800002494018006887460000')
                + struct.pack('<III', BASE+24, BASE+32, BASE+34)
                + bytes.fromhex('00bd00bd00bd'))
        _, result = self.run_scanner(data)
        record = next(r for r in result['transfer_records'] if r['kind'] == 'bounded_switch')
        self.assertEqual(record['default_target'], BASE+36)
        self.assertTrue({BASE+32, BASE+34, BASE+36} <= result['return_sites'])

    def test_arm_pc_bias_and_thumb_state_are_preserved(self):
        scanner, result = self.run_scanner(bytes.fromhex('01008fe210ff2fe17047'), 'ARM')
        self.assertIn((BASE+8, 'Thumb'), scanner.entries)
        self.assertEqual(result['unresolved_transfers'], set())

    def test_conditional_literal_load_does_not_invent_a_target(self):
        data = (bytes.fromhex('04009f0510ff2fe100000000')
                + struct.pack('<I', BASE+16) + bytes.fromhex('1eff2fe1'))
        scanner, result = self.run_scanner(data, 'ARM')
        self.assertEqual(result['unresolved_transfers'], {BASE+4})
        self.assertNotIn((BASE+16, 'ARM'), scanner.entries)

    def test_conditional_return_keeps_the_fallthrough_path(self):
        _, result = self.run_scanner(bytes.fromhex('1eff2f111eff2fe1'), 'ARM')
        self.assertEqual(result['return_sites'], {BASE, BASE+4})

    def test_unmodelled_shift_cannot_fabricate_an_interworking_target(self):
        scanner, result = self.run_scanner(bytes.fromhex('0f10a0e10120a0e3020181e010ff2fe1'), 'ARM')
        self.assertIn(BASE+12, result['unresolved_transfers'])
        self.assertNotIn((BASE+8, 'Thumb'), scanner.entries)

    def test_literal_target_through_register_veneer(self):
        data = (bytes.fromhex('024d00f005f8704700000000') + struct.pack('<I', BASE+21)
                + bytes.fromhex('284700007047'))
        scanner, result = self.run_scanner(data)
        record = next(r for r in result['transfer_records'] if r['kind'] == 'register_veneer_call')
        self.assertTrue(record['targets_complete'])
        self.assertEqual(record['targets'], [BASE+20])
        self.assertIn((BASE+20, 'Thumb'), scanner.entries)

    def test_direct_call_to_bx_lr_is_not_a_callback(self):
        _, result = self.run_scanner(bytes.fromhex('00f002f8704700007047'))
        self.assertFalse(any(r['kind'] == 'register_veneer_call' for r in result['transfer_records']))

    def test_unknown_callback_is_not_given_a_fictional_target(self):
        _, result = self.run_scanner(bytes.fromhex('00f002f8704700000047'))
        record = next(r for r in result['transfer_records'] if r['kind'] == 'register_veneer_call')
        self.assertFalse(record['targets_complete'])
        self.assertEqual(record['targets'], [])

    def test_stack_adjustment_keeps_return_but_register_write_does_not(self):
        _, result = self.run_scanner(bytes.fromhex('02bc01b00847'))
        self.assertEqual(result['unresolved_transfers'], set())
        self.assertEqual(result['return_sites'], {BASE+4})
        _, result = self.run_scanner(bytes.fromhex('02bc01310847'))
        self.assertEqual(result['unresolved_transfers'], {BASE+4})

    def test_unmodelled_pc_writes_do_not_fall_through_to_a_fake_return(self):
        for data, mode in [(bytes.fromhex('87447047'), 'Thumb'),
                           (bytes.fromhex('00f090e51eff2fe1'), 'ARM')]:
            with self.subTest(mode=mode):
                _, result = self.run_scanner(data, mode)
                self.assertEqual(result['unresolved_transfers'], {BASE})
                self.assertEqual(result['return_sites'], set())

    def test_weak_fallthrough_label_is_not_a_function_boundary(self):
        for evidence, expected in [('pointer candidate', True), ('direct call', False)]:
            scanner = Scanner(bytes.fromhex('002001217047'), [])
            scanner.seed(BASE, 'Thumb', 'startup')
            scanner.seed(BASE+2, 'Thumb', evidence)
            scanner.drain()
            self.assertEqual(BASE+2 in scanner.results[(BASE, 'Thumb')]['instructions'], expected)
            self.assertEqual(BASE+2 in scanner.internal_labels, expected)
