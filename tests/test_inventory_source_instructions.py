"""Explicit assembly provenance stays separate from rooted CFG byte roles."""
import copy
import hashlib
import json
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from inventory_rom import source_owned_instruction_regions
from inventory_census import census, verify_census
from inventory_partition import partition, verify_discovery


class SourceInstructionTests(unittest.TestCase):
    def fixture(self, source=None, data=None):
        source = source if source is not None else (
            '.syntax unified\n.cpu arm7tdmi\n.thumb\n.text\n.balign 4, 0\n'
            '.global _call_via_r0\n.type _call_via_r0, %function\n.thumb_func\n'
            '_call_via_r0:\n    bx r0\n    nop\n.size _call_via_r0, .-_call_via_r0\n').encode()
        data = bytes.fromhex('0047c04600000000') if data is None else data
        owner = dict(name='_call_via_r0', source='src/frame/call_via_r0.s',
                     rom_offset=0, size=4, kind='assembly_glue', source_kind='assembly_glue',
                     mode='Thumb', source_sha256=hashlib.sha256(source).hexdigest())
        row = dict(name='authored_nop', owner=owner['name'], source=owner['source'],
                   rom_offset=2, size=2, mode='Thumb', instruction='nop', source_line=11,
                   proof_kind='thumb_register_veneer_nop_v1', source_sha256=owner['source_sha256'],
                   region_sha256=hashlib.sha256(data[2:4]).hexdigest(),
                   evidence=['Explicit source NOP, fixed Thumb decode and reviewed source-object mapping.'])
        return data, owner, row, source

    def validate(self, row=None, owner=None, source=None, data=None):
        data, default_owner, default_row, source = self.fixture(source, data)
        return source_owned_instruction_regions(data, [default_row if row is None else row],
            [default_owner if owner is None else owner], lambda unused: source)

    def test_explicit_source_native_NOP_preserves_metadata_and_input(self):
        data, owner, row, source = self.fixture()
        before = copy.deepcopy(row)
        self.assertEqual(self.validate(), [{**row, 'status':'source_authored_instruction'}])
        self.assertEqual(row, before)
        self.assertEqual(source_owned_instruction_regions(data, [], [],
            lambda unused: self.fail('Empty annotations must not read source')), [])

    def test_stale_source_span_hash_and_changed_native_owner_rejected(self):
        data, owner, row, source = self.fixture()
        for change in [dict(source_sha256='0'*64), dict(region_sha256='0'*64)]:
            with self.subTest(change=change), self.assertRaises(ValueError):
                self.validate({**row, **change})
        # The preceding BX is part of the actual supported native/source grammar,
        # even though the annotated NOP bytes and their hash remain unchanged.
        with self.assertRaises(ValueError):
            self.validate(data=bytes.fromhex('0847c04600000000'))
        with self.assertRaises(ValueError):
            self.validate(data=bytes.fromhex('0047012000000000'))

    def test_foreign_C_data_owner_mode_bounds_and_alignment_rejected(self):
        data, owner, row, source = self.fixture()
        bad_rows = [dict(owner='missing'), dict(owner=[]), dict(source='foreign.s'),
                    dict(mode='ARM'), dict(rom_offset=1), dict(rom_offset=4),
                    dict(rom_offset=True), dict(size=1), dict(size=4),
                    dict(source_line=10), dict(instruction='mov'),
                    dict(proof_kind='arbitrary_decodable_span'), dict(evidence=[]), dict(evidence=['']),
                    dict(source_reconstruction_verified=True)]
        for change in bad_rows:
            with self.subTest(change=change), self.assertRaises(ValueError):
                self.validate({**row, **change})
        for change in [dict(kind='compiled_c', source='actual.c'), dict(mode='data'),
                       dict(mode='ARM'), dict(size=8), dict(rom_offset=2), dict(name='foreign')]:
            with self.subTest(owner=change), self.assertRaises(ValueError):
                self.validate(owner={**owner, **change})
        for value in [None, {}, [None]]:
            with self.subTest(value=value), self.assertRaises(ValueError):
                source_owned_instruction_regions(data, value, [owner], lambda unused: source)

    def test_hash_updates_cannot_turn_fill_data_macros_or_other_mnemonics_into_NOP(self):
        data, owner, row, source = self.fixture()
        for replacement in ['.short 0x46c0', '.word 0x46c0', '.balign 4, 0',
                            '.incbin "original.bin"', 'mov r8, r8', 'my_nop_macro']:
            changed = source.replace(b'    nop\n', ('    '+replacement+'\n').encode())
            with self.subTest(replacement=replacement), self.assertRaises(ValueError):
                # Fresh source hashes isolate the explicit mnemonic grammar check.
                self.validate(source=changed)
        with self.assertRaises(ValueError):
            self.validate(source=source.replace(b'bx r0', b'bx r1'))

    def test_duplicate_names_overlaps_and_missing_provenance_rejected(self):
        data, owner, row, source = self.fixture()
        for other in [row, {**row, 'name':'another'}]:
            with self.subTest(other=other), self.assertRaises(ValueError):
                source_owned_instruction_regions(data, [row, other], [owner], lambda unused: source)
        with self.assertRaises(ValueError):
            source_owned_instruction_regions(data, [row], [owner, owner], lambda unused: source)
        for field in ['source_sha256','region_sha256','source','source_line','mode','evidence']:
            changed = dict(row);changed.pop(field)
            with self.subTest(field=field), self.assertRaises(ValueError):
                self.validate(changed)

    def run_census(self, *, authored=True, rooted_NOP=False, ARM=False, literals=(), known=False, exclude=False, dual_use=False):
        data, owner, row, source = self.fixture()
        class Scanner:
            copies = []
            def physical(self, address):
                return address-0x1000 if 0x1000<=address<0x1008 else None
        scanner=Scanner();scanner.data=data
        key=0x1000,'Thumb'; entries={key:dict(evidence={'bounded audit'}, name=owner['name'])}
        instructions={0x1000:2, **({0x1002:2} if rooted_NOP or exclude else {})}
        observations={key:dict(instructions=instructions, literals=set(literals))}
        if ARM:
            entries[(0x1000,'ARM')]=dict(evidence={'startup'}, name='opposite mode')
            observations[(0x1000,'ARM')]=dict(instructions={0x1000:4}, literals=set())
        annotations=[dict(kind='exclude_observation', entry=0x1000, mode='Thumb',
            instruction_ranges=[[2,4]], reason='Excluded context remains visible',
            evidence=['Reviewed context-specific exclusion'])] if exclude else []
        if dual_use:
            annotations.append(dict(kind='dual_use',ranges=[[2,4]],reason='Actual rooted code word read',
                                    evidence=['Rooted instruction and reference at the same halfword']))
        result=census(scanner, entries, observations, source_code=[owner],
            data_regions=[dict(rom_offset=2,size=2)] if known else [],
            quality_annotations=annotations,
            source_instruction_regions=self.validate() if authored else [])
        result=json.loads(json.dumps(result));self.assertTrue(verify_census(result,len(data)))
        return result

    def role_at_NOP(self, result):
        return next(row for row in result['partition'] if row['rom_offset']<=2<row['rom_offset']+row['size'])

    def test_authored_only_roles_add_no_roots_CFG_bytes_credit_or_denominator(self):
        before,after=self.run_census(authored=False),self.run_census()
        self.assertEqual(self.role_at_NOP(before)['classification'],'owned_extent_unclassified')
        self.assertEqual(self.role_at_NOP(after)['classification'],'source_authored_unrooted_instruction')
        self.assertEqual(after['physical_unions']['source_instruction_Thumb'],[[2,4]])
        self.assertEqual(after['physical_unions']['source_instruction_ARM'],[])
        self.assertEqual(after['counts']['source_authored_instruction_union_bytes'],2)
        for key in ['instruction','raw_instruction','ARM','Thumb','referenced_data','source_owned']:
            self.assertEqual(before['physical_unions'][key],after['physical_unions'][key])
        for key in ['strong_execution_entries','unique_physical_entries','entry_boundary_observations']:
            self.assertEqual(before[key],after[key])
        for key in ['raw_instruction_union_bytes','qualified_observed_instruction_union_bytes',
                    'nonconflicting_qualified_instruction_bytes','source_glue_owned_extent_bytes']:
            self.assertEqual(before['counts'][key],after['counts'][key])
        for result in [before,after]:
            self.assertFalse(result['complete_code_inventory']);self.assertFalse(result['single_code_denominator_established'])
            self.assertFalse(result['recovered_source_credit_changed']);self.assertEqual(result['runtime_observations'],0)

    def test_same_mode_rooted_precedence_preserves_authored_provenance(self):
        result=self.run_census(rooted_NOP=True)
        self.assertEqual(self.role_at_NOP(result)['classification'],'strong_rooted_instruction')
        self.assertIn('source_instruction_Thumb',self.role_at_NOP(result)['roles'])
        self.assertEqual(result['counts']['qualified_observed_instruction_union_bytes'],4)
        self.assertEqual(result['strong_execution_entries'],1)

    def test_authored_opposite_mode_and_data_conflicts_survive(self):
        for options,expected in [({'ARM':True},'ambiguous_mode_conflict'),
                                 ({'known':True},'ambiguous_instruction_known_data'),
                                 ({'literals':(2,3)},'ambiguous_instruction_data_overlap'),
                                 ({'rooted_NOP':True,'known':True},'ambiguous_instruction_known_data')]:
            with self.subTest(options=options):
                result=self.run_census(**options)
                self.assertEqual(self.role_at_NOP(result)['classification'],expected)
                self.assertIn('source_instruction_Thumb',self.role_at_NOP(result)['roles'])
        result=self.run_census(rooted_NOP=True,literals=(2,3),dual_use=True)
        self.assertEqual(self.role_at_NOP(result)['classification'],'instruction_and_referenced_data_dual_use')
        # An authored annotation alone cannot manufacture a new dual-use approval.
        with self.assertRaises(ValueError):
            data,owner,row,source=self.fixture()
            class Scanner:
                copies=[]
                def physical(self,address):return address-0x1000
            scanner=Scanner();scanner.data=data
            census(scanner,{}, {},source_code=[owner],data_regions=[],
                source_instruction_regions=self.validate(),quality_annotations=[
                    dict(kind='dual_use',ranges=[[2,4]],reason='invented',evidence=['authored only'])])

    def test_excluded_raw_instruction_retains_role_and_contingent_class(self):
        result=self.run_census(exclude=True);part=self.role_at_NOP(result)
        self.assertEqual(part['classification'],'contingent_unqualified_observation')
        for role in ['raw_instruction','excluded_observation','source_instruction_Thumb']:
            self.assertIn(role,part['roles'])
        self.assertEqual(result['counts']['raw_instruction_union_bytes'],4)
        self.assertEqual(result['counts']['qualified_observed_instruction_union_bytes'],2)

    def test_verifier_reconstructs_roles_from_annotations_and_owner_membership(self):
        good=self.run_census();before=self.run_census(authored=False)
        # Accounting remains internally consistent with the original unannotated
        # partition/counts; the missing annotation-to-role relationship must fail.
        changed=copy.deepcopy(before)
        for key in ['source_owned_instruction_regions','source_extent_ownership']:
            changed[key]=copy.deepcopy(good[key])
        with self.assertRaises(ValueError):verify_census(changed,8)
        for change in [lambda d:d['source_owned_instruction_regions'].clear(),
                       lambda d:d['source_owned_instruction_regions'][0].update(owner='foreign'),
                       lambda d:d['source_owned_instruction_regions'][0].update(source='foreign.s'),
                       lambda d:d['source_owned_instruction_regions'][0].update(source_sha256='0'*64),
                       lambda d:d['source_owned_instruction_regions'][0].update(mode='ARM'),
                       lambda d:d['source_owned_instruction_regions'][0].update(rom_offset=0),
                       lambda d:d['source_extent_ownership'][0].update(source_instruction_regions=[]),
                       lambda d:d.update(recovered_source_credit_changed=True)]:
            changed=copy.deepcopy(good);change(changed)
            with self.subTest(change=change),self.assertRaises(ValueError):verify_census(changed,8)

    def inventory(self):
        result=self.run_census();row=dict(name='owner',rom_offset=0,size=4,status='mapped_code')
        source=result['source_owned_instruction_regions'][0]
        return dict(reference_sha256='ref',rom_bytes=8,complete_rom_partition=True,
            complete_code_inventory=False,inventory_schema_version=2,historical_mapped_extent_baseline=319640,
            entry_count=1,extent_count=1,mapped_extent_bytes=4,rows=[row],data_regions=[],
            partition=partition([row],8),code_census=result,
            source_owned_instruction_regions=copy.deepcopy(result['source_owned_instruction_regions']),
            input_sha256={source['source']:source['source_sha256']})

    def test_output_source_hash_and_annotation_metadata_are_bound(self):
        good=self.inventory();verify_discovery(good,8,'ref')
        for change in [lambda d:d['source_owned_instruction_regions'].clear(),
                       lambda d:d['input_sha256'].clear(),
                       lambda d:d['code_census']['source_owned_instruction_regions'][0].update(source_line=12)]:
            changed=copy.deepcopy(good);change(changed)
            with self.assertRaises(ValueError):verify_discovery(changed,8,'ref')

    def test_legacy_empty_annotations_need_no_new_source_provenance(self):
        legacy=self.run_census(authored=False)
        legacy.pop('source_owned_instruction_regions')
        legacy['classification_definitions'].pop('source_authored_unrooted_instruction')
        legacy['counts'].pop('source_authored_instruction_union_bytes')
        for mode in ['ARM','Thumb']:legacy['physical_unions'].pop('source_instruction_'+mode)
        self.assertTrue(verify_census(legacy,8))
        # Omitting only one new mode is neither an old schema nor a complete new one.
        changed=self.run_census(authored=False);changed['physical_unions'].pop('source_instruction_ARM')
        with self.assertRaises(ValueError):verify_census(changed,8)

    def test_all_fifteen_manifest_controls_mutate_the_actual_annotated_NOP(self):
        root=Path(__file__).resolve().parents[1]
        config=json.loads((root/'config/code-evidence-us-eu.json').read_text())
        manifest=json.loads((root/'config/build-us-eu.json').read_text())
        annotations=config['source_owned_instruction_regions'];self.assertEqual(len(annotations),15)
        owners={row['name']:row for row in manifest['assembly']}
        for row in annotations:
            owner=owners[row['owner']];source=(root/owner['source']).read_bytes()
            self.assertEqual(owner['negative_control'],dict(before='nop',after='movs r0, #1'))
            self.assertEqual(hashlib.sha256(source).hexdigest(),row['source_sha256'])
            self.assertEqual(source.decode().splitlines()[row['source_line']-1].strip(),'nop')
            self.assertEqual(source.decode().count('nop'),1)


if __name__=='__main__':
    unittest.main()
