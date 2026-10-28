"""Only natural linker alignment may separate glue storage from its entry."""
from pathlib import Path
import os
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import source_addresses

try:
    from elftools.elf.elffile import ELFFile
    from pilot import assemble_glue
except ModuleNotFoundError as error:
    if error.name != 'elftools':
        raise
    assemble_glue = None

ASSEMBLER = ROOT / 'toolchains/binutils/bin/arm-none-eabi-as'
LINKER = ROOT / 'toolchains/binutils/bin/arm-none-eabi-ld'
NO_OFFSET = object()
REJECTION = r'(?i)entry|align|prefix|function|extent'


class GlueEntryAddressTests(unittest.TestCase):
    def region(self, **changes):
        return {'name': 'fixture', 'rom_offset': 0x2A8, 'size': 68,
                'mode': 'ARM', 'kind': 'assembly_glue', 'entry_offset': 8,
                **changes}

    def test_entry_offset_does_not_move_storage_address(self):
        for mode in ('ARM', 'Thumb'):
            with self.subTest(mode=mode):
                region = self.region(mode=mode)
                self.assertEqual(source_addresses.execution_address(region),
                                 0x080002A8)
                self.assertEqual(source_addresses.entry_address(region),
                                 0x080002B0)

    def test_missing_field_keeps_existing_c_entry(self):
        function = {'name': 'fixture', 'rom_offset': 0x2A8, 'size': 60}
        self.assertEqual(source_addresses.entry_address(function), 0x080002A8)

    def test_copied_assembly_entry_uses_ram_base_and_full_storage_extent(self):
        copies = [{'name': 'fixture_copy', 'rom_offset': 0x1000,
                   'ram_address': 0x03001000, 'size': 80}]
        region = self.region(rom_offset=0x1008, ram_address=0x03001008,
                             ram_copy='fixture_copy')
        self.assertEqual(source_addresses.execution_address(region, copies),
                         0x03001008)
        self.assertEqual(source_addresses.entry_address(region, copies),
                         0x03001010)
        # The eight prefix bytes still belong to the installation extent.
        with self.assertRaises(ValueError):
            source_addresses.entry_address({**region, 'size': 76}, copies)

    def test_observed_mode_is_checked_at_real_copied_entry(self):
        copies = [{'name': 'fixture_copy', 'rom_offset': 0x1000,
                   'ram_address': 0x03001000, 'size': 80}]
        region = self.region(rom_offset=0x1008, ram_address=0x03001008,
                             ram_copy='fixture_copy')
        entries = [{'ram_address': 0x03001010, 'mode': 'Thumb'}]
        with self.assertRaisesRegex(ValueError, r'(?i)entry|mode'):
            source_addresses.entry_address(region, copies, entries)

    def test_explicit_field_is_rejected_for_c_data_and_nondefining_storage(self):
        for offset in (0, 8):
            variants = [self.region(entry_offset=offset),
                        self.region(entry_offset=offset, kind='source_data'),
                        self.region(entry_offset=offset, defines_symbol=False)]
            del variants[0]['kind']  # A C function is not assembly glue.
            for region in variants:
                with self.subTest(region=region), self.assertRaisesRegex(
                        ValueError, REJECTION):
                    source_addresses.entry_address(region)

    def test_invalid_offsets_are_rejected(self):
        for offset in (-4, 2, 68, 72, True, False, 8.0, '8', None):
            with self.subTest(offset=offset), self.assertRaisesRegex(
                    ValueError, REJECTION):
                source_addresses.entry_address(self.region(entry_offset=offset))

    def test_definition_alias_uses_entry_instead_of_prefix_address(self):
        region = self.region()
        caller = {'name': 'caller', 'rom_offset': 0x400, 'size': 4,
                  'symbols': {'fixture': '0x080002B0'}}
        manifest = {'functions': [caller], 'assembly': [region]}
        source_addresses.validate_symbol_definitions(manifest)
        caller['symbols']['fixture'] = '0x080002A8'
        with self.assertRaisesRegex(ValueError, r'(?i)entry|execution address'):
            source_addresses.validate_symbol_definitions(manifest)


@unittest.skipUnless(assemble_glue is not None and
                     all(path.is_file() and os.access(path, os.X_OK)
                         for path in (ASSEMBLER, LINKER)),
                     'Native assembly fixtures require make setup; no ROM is needed')
class GlueEntryOffsetNativeTests(unittest.TestCase):
    def assemble(self, *, mode='ARM', alignment=16, before='', extra='',
                 symbol_type='%function', symbol_size='.-fixture',
                 offset=8, extent=68, rom_offset=0x2A8,
                 declared_name='fixture', defines_symbol=True, extra_region=None):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        folder = Path(temporary.name).resolve()
        source = folder / 'fixture.s'
        # Fourteen ordinary additions and a return give 60 ARM bytes. There
        # is no leading source padding and no game input or copied code.
        body = ('.rept 14\nadd r0, r0, #1\n.endr\nbx lr\n'
                if mode == 'ARM' else 'adds r0, r0, #1\nbx lr\n')
        source.write_text(
            f'.syntax unified\n.text\n.balign {alignment},0\n'
            f'.{mode.lower()}\n.global fixture\n.type fixture,{symbol_type}\n'
            + before + ('.thumb_func\n' if mode == 'Thumb' else '')
            + 'fixture:\n' + body + f'.size fixture,{symbol_size}\n' + extra)
        region = {'name': declared_name, 'rom_offset': rom_offset, 'size': extent,
                  'mode': mode, 'kind': 'assembly_glue',
                  'defines_symbol': defines_symbol, **(extra_region or {})}
        if offset is not NO_OFFSET:
            region['entry_offset'] = offset
        proof = folder / 'proof'
        data, commands = assemble_glue(region, source, proof)
        return region, proof, data, commands

    def assert_natural_entry(self, region, proof, data, commands, input_size):
        base = 0x08000000 + region['rom_offset']
        entry = source_addresses.entry_address(region)
        prefix = region['entry_offset']
        self.assertTrue(commands)
        with (proof / 'source.o').open('rb') as stream:
            elf = ELFFile(stream)
            text = elf.get_section_by_name('.text')
            functions = [s for s in elf.get_section_by_name('.symtab').iter_symbols()
                         if s['st_info']['type'] == 'STT_FUNC' and
                         s['st_shndx'] == elf.get_section_index('.text')]
            self.assertEqual(len(functions), 1)
            self.assertEqual(functions[0].name, 'fixture')
            self.assertEqual(functions[0]['st_value'] & ~1, 0)
            self.assertEqual(functions[0]['st_size'], input_size)
            self.assertEqual(text['sh_addralign'], 16)
            self.assertEqual((-base) % text['sh_addralign'], prefix)
            input_text = text.data()
            self.assertEqual(len(input_text), input_size)
        self.assertEqual(len(data), region['size'])
        self.assertEqual(data, bytes(prefix) + input_text)
        with (proof / 'linked.elf').open('rb') as stream:
            elf = ELFFile(stream)
            text = elf.get_section_by_name('.text')
            self.assertEqual(text['sh_addr'], base)
            self.assertEqual(text.data(), data)
            functions = [s for s in elf.get_section_by_name('.symtab').iter_symbols()
                         if s['st_info']['type'] == 'STT_FUNC' and
                         s['st_shndx'] == elf.get_section_index('.text')]
            self.assertEqual(len(functions), 1)
            symbol = functions[0]
            self.assertEqual(symbol['st_value'] & ~1, entry)
            self.assertEqual(elf['e_entry'] & ~1, entry)
            mode_bit = int(region['mode'] == 'Thumb')
            self.assertEqual(symbol['st_value'] & 1, mode_bit)
            self.assertEqual(elf['e_entry'] & 1, mode_bit)

    def test_arm_natural_prefix_has_exact_60_byte_function_and_68_byte_extent(self):
        region, proof, data, commands = self.assemble()
        self.assert_natural_entry(region, proof, data, commands, 60)

    def test_thumb_natural_prefix_preserves_thumb_symbol_and_entry_bits(self):
        region, proof, data, commands = self.assemble(mode='Thumb', extent=12)
        self.assert_natural_entry(region, proof, data, commands, 4)

    def test_aligned_input_accepts_explicit_zero_offset(self):
        region, proof, data, commands = self.assemble(
            offset=0, extent=60, rom_offset=0x2B0)
        self.assert_natural_entry(region, proof, data, commands, 60)

    def test_missing_offset_cannot_silently_admit_natural_prefix(self):
        with self.assertRaisesRegex((ValueError, RuntimeError), REJECTION):
            self.assemble(offset=NO_OFFSET)

    def test_renamed_metadata_cannot_hide_an_undeclared_natural_prefix(self):
        with self.assertRaisesRegex((ValueError, RuntimeError), REJECTION):
            self.assemble(offset=NO_OFFSET, declared_name='different_entry')

    def test_nondefining_renamed_metadata_cannot_hide_a_natural_prefix(self):
        with self.assertRaisesRegex((ValueError, RuntimeError), REJECTION):
            self.assemble(offset=NO_OFFSET, declared_name='different_entry',
                          defines_symbol=False)

    def test_explicit_prefix_assembly_rejects_ram_execution_fields(self):
        variants = [{'ram_address': 0x030002A8},
                    {'ram_copy': 'fixture_copy'},
                    {'ram_address': 0x030002A8, 'ram_copy': 'fixture_copy'}]
        for fields in variants:
            with self.subTest(fields=fields), self.assertRaisesRegex(
                    (ValueError, RuntimeError), REJECTION):
                self.assemble(extra_region=fields)

    def test_wrong_or_zero_offset_cannot_admit_natural_prefix(self):
        for offset in (0, 4, 12):
            with self.subTest(offset=offset), self.assertRaisesRegex(
                    (ValueError, RuntimeError), REJECTION):
                self.assemble(offset=offset)

    def test_source_space_cannot_impersonate_a_natural_prefix(self):
        # Alignment four adds no linker prefix at 2A8. An object-local eight
        # byte gap would nevertheless put the final symbol at the tempting 2B0.
        with self.assertRaisesRegex((ValueError, RuntimeError), REJECTION):
            self.assemble(alignment=4, before='.space 8,0\n')

    def test_source_prefix_is_rejected_without_an_offset_declaration(self):
        with self.assertRaisesRegex((ValueError, RuntimeError), REJECTION):
            self.assemble(alignment=4, before='.space 8,0\n', offset=NO_OFFSET)

    def test_nonfunction_symbol_cannot_claim_an_entry(self):
        with self.assertRaisesRegex((ValueError, RuntimeError), REJECTION):
            self.assemble(symbol_type='%object')

    def test_zero_sized_function_cannot_claim_an_entry(self):
        with self.assertRaisesRegex((ValueError, RuntimeError), REJECTION):
            self.assemble(symbol_size='0')

    def test_second_function_is_not_hidden_inside_the_claimed_extent(self):
        extra = ('.global second\n.type second,%function\nsecond:\n'
                 'bx lr\n.size second,.-second\n')
        with self.assertRaisesRegex((ValueError, RuntimeError), REJECTION):
            self.assemble(extra=extra, extent=72)

    def test_declared_extent_cannot_omit_or_add_bytes(self):
        for extent in (64, 72):
            with self.subTest(extent=extent), self.assertRaisesRegex(
                    (ValueError, RuntimeError), REJECTION):
                self.assemble(extent=extent)

    def test_existing_aligned_glue_needs_no_entry_offset(self):
        _, _, data, _ = self.assemble(offset=NO_OFFSET, extent=60,
                                       rom_offset=0x2B0)
        self.assertEqual(len(data), 60)
