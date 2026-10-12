#!/usr/bin/env python3
"""Link matching C objects and explicitly unconverted ROM gaps; never patch output."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
from elftools.elf.elffile import ELFFile
from project import ROOT, audit, compare_bytes, write_report
from pilot import compile_function, run
from rom_layout import layout




def link_rom(manifest, reference, pilot_folder, folder, overrides=None):
    folder.mkdir(parents=True, exist_ok=True)
    commands, objects, script, gaps = [], [], ['SECTIONS {'], []
    regions = layout(manifest['functions'], manifest['rom_size'])
    overrides = overrides or {}
    names = {f['name'] for f in manifest['functions']}
    symbols = {}
    for f in manifest['functions']:
        for name, value in f.get('symbols', {}).items():
            if name not in names:
                if name in symbols and symbols[name] != value:
                    raise ValueError('Conflicting external symbol address')
                symbols[name] = value
    externs = []
    for name, value in symbols.items():
        externs += [f'.global {name}']
        externs += ([f'.type {name}, %function', f'.thumb_set {name}, {value}']
                    if name in ('frame_update', '_call_via_r0') else [f'.set {name}, {value}'])
    extern_path = folder / 'externs.s'
    extern_path.write_text('\n'.join(externs) + '\n')
    extern_obj = folder / 'externs.o'
    assembler = ROOT / 'toolchains/binutils/bin/arm-none-eabi-as'
    run([assembler, extern_path, '-o', extern_obj], commands)
    objects.append(extern_obj)
    for index, region in enumerate(regions):
        section = f'.rom_{index}'
        start = 0x08000000 + region['offset']
        if region['kind'] == 'compiled_c':
            obj = overrides.get(region['name'], pilot_folder / region['name'] / 'source.o')
            with obj.open('rb') as stream:
                elf = ELFFile(stream)
                if any(s['sh_flags'] & 2 and s['sh_size'] and s.name != '.text' for s in elf.iter_sections()):
                    raise ValueError('Unexpected allocated source section')
            objects.append(obj)
            body = f'{obj}(.text) . = ALIGN(4);'
        else:
            gaps += [f'.section .gap_{index}, "a", %progbits',
                     f'.incbin {json.dumps(str(reference))}, {region["offset"]}, {region["size"]}']
            body = f'*(.gap_{index})'
        script += [f'{section} {start:#x} : {{ {body} }} = 0',
                   f'ASSERT(SIZEOF({section}) == {region["size"]}, "extent {index} changed")']
    script += ['/DISCARD/ : { *(.comment) *(.note*) *(.ARM.attributes) }', '}']
    gap_source, gap_obj = folder / 'unconverted.s', folder / 'unconverted.o'
    gap_source.write_text('\n'.join(gaps) + '\n')
    run([assembler, gap_source, '-o', gap_obj], commands)
    objects.append(gap_obj)
    script_path = folder / 'rom.ld'
    script_path.write_text('\n'.join(script) + '\n')
    linked, output = folder / 'bustin-out.elf', folder / 'bustin-out.gba'
    run([ROOT / 'toolchains/binutils/bin/arm-none-eabi-ld', '-T', script_path,
         '-Map', folder / 'bustin-out.map', *objects, '-o', linked], commands)
    with linked.open('rb') as stream:
        elf = ELFFile(stream)
        allocated = [s for s in elf.iter_sections() if s['sh_flags'] & 2 and s['sh_size']]
        if len(allocated) != len(regions):
            raise ValueError('Unexpected extra allocated ROM section')
        for section, region in zip(allocated, regions):
            if section['sh_addr'] != 0x08000000 + region['offset'] or section['sh_size'] != region['size']:
                raise ValueError('Final ELF layout differs from declared coverage')
        if any(s['sh_type'] in ('SHT_REL', 'SHT_RELA') and s['sh_size'] for s in elf.iter_sections()):
            raise ValueError('Final ELF contains relocations')
    run([ROOT / 'toolchains/binutils/bin/arm-none-eabi-objcopy', '-O', 'binary', linked, output], commands)
    return output, regions, commands


def main():
    # Fresh compilation verifies pinned compiler, headers, objects and reference.
    subprocess.run([sys.executable, ROOT / 'tools/pilot.py', '--negative-control'], check=True)
    pilot = json.loads((ROOT / 'reports/us-eu/pilot.json').read_text())
    if not pilot['accepted']:
        raise ValueError('Source gate failed')
    manifest = json.loads((ROOT / 'config/build-us-eu.json').read_text())
    target = json.loads((ROOT / 'config/targets/us-eu.json').read_text())
    manifest['rom_size'] = target['size']
    reference = ROOT / target['rom_path']
    rom, identity = audit(reference, target)
    if not identity['accepted']:
        raise ValueError('Reference changed')
    pilot_folder = Path(pilot['output_directory'])
    folder = ROOT / 'build/us-eu/runs' / pilot['run_id']
    output, regions, commands = link_rom(manifest, reference, pilot_folder, folder)
    comparison = compare_bytes(rom, output.read_bytes())
    # A same-size real source mutation must propagate through the whole-ROM link.
    f = next(f for f in manifest['functions'] if f['name'] == 'configure_blending')
    changed_folder = folder / 'negative-source'
    changed_folder.mkdir()
    changed = changed_folder / 'changed.c'
    original = (pilot_folder / f['name'] / 'source.c').read_text()
    if '16' not in original:
        raise ValueError('Negative control edit no longer applies')
    changed.write_text(original.replace('16', '15'))
    _, negative_compile_commands = compile_function(f, changed, changed_folder, manifest['compiler_flags'])
    bad_output, _, bad_commands = link_rom(manifest, reference, pilot_folder, folder / 'negative-link',
                                         {f['name']: changed_folder / 'source.o'})
    negative = compare_bytes(rom, bad_output.read_bytes())
    rejected = not negative['identical'] and negative['candidate_size'] == len(rom)
    report = {'target': 'us-eu', 'run_id': pilot['run_id'], 'output': str(output),
              'reference_sha256': identity['sha256'], 'pilot_report': str(pilot_folder / 'report.json'),
              'comparison': comparison, 'negative_control': negative, 'negative_control_rejected': rejected,
              'compiled_c_functions': len(manifest['functions']),
              'compiled_c_bytes_including_pools_and_alignment': sum(f['size'] for f in manifest['functions']),
              'unconverted_bytes': sum(r['size'] for r in regions if r['kind'] == 'unconverted'),
              'full_source_reconstruction': False, 'regions': regions, 'commands': commands,
              'negative_source': str(changed),
              'negative_source_sha256': hashlib.sha256(changed.read_bytes()).hexdigest(),
              'negative_compile_commands': negative_compile_commands,
              'negative_link_commands': bad_commands,
              'helper_sha256': {name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
                                for name in ('tools/build_rom.py', 'tools/rom_layout.py')},
              'accepted': comparison['identical'] and rejected}
    (folder / 'report.json').write_text(json.dumps(report, indent=2) + '\n')
    write_report('build', report)
    if not report['accepted']:
        return 1
    # Publish verified output only. No bytes are repaired or patched.
    (ROOT / 'build/us-eu/bustin-out.gba').write_bytes(output.read_bytes())
    print(f"Whole ROM: MATCH; {report['compiled_c_functions']} C functions, "
          f"{report['compiled_c_bytes_including_pools_and_alignment']} source bytes; "
          f"{report['unconverted_bytes']} explicitly unconverted bytes")
    print('Changed-source whole-ROM negative control: REJECTED')
    return 0


if __name__ == '__main__':
    sys.exit(main())
