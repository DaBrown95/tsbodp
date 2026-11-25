#!/usr/bin/env python3
"""Derive a revision 1 build manifest and RAM map from the revision 0 sources.

Inputs are the two pinned reference ROMs, the revision 0 manifest and RAM map,
and the object files of the latest accepted revision 0 pilot run. Nothing here
grants source credit: every derived entry must still pass the normal pilot,
whole-ROM and changed-source gates against the revision 1 reference.

A source extent is carried over when its revision 0 bytes, with relocation
fields masked, occur in revision 1 at a position consistent with its
neighbours. External symbol values come from the relocation fields of the
revision 1 bytes. Extents that cannot be placed are reported, not guessed.
"""
import argparse
import bisect
import collections
import hashlib
import json
import struct
import sys
from pathlib import Path
from elftools.elf.elffile import ELFFile
from project import ROOT, audit

ROM_BASE = 0x08000000
CODE_LIMIT = 0x60000
R_ARM_ABS32, R_ARM_THM_CALL = 2, 10
R_ARM_CALLS = (1, 28, 29)


def word(data, offset):
    return struct.unpack_from('<I', data, offset)[0]


def thumb_bl_target(data, offset):
    high, low = struct.unpack_from('<HH', data, offset)
    delta = ((high & 0x7ff) << 12) | ((low & 0x7ff) << 1)
    if delta & 0x400000:
        delta -= 0x800000
    return ROM_BASE + offset + 4 + delta


def arm_bl_target(data, offset):
    delta = word(data, offset) & 0xffffff
    if delta & 0x800000:
        delta -= 0x1000000
    return ROM_BASE + offset + 8 + delta * 4


def masked(data, limit):
    """Hide words that typically hold addresses or branch offsets."""
    out = bytearray(data[:limit])
    for i in range(0, limit - 3, 4):
        if out[i + 3] in (0x02, 0x03, 0x08, 0x09, 0xEB):
            out[i:i + 3] = b'\0\0\0'
    i = 0
    while i < limit - 2:
        high, low = struct.unpack_from('<HH', out, i)
        if high & 0xF800 == 0xF000 and low & 0xF800 == 0xF800:
            struct.pack_into('<HH', out, i, 0xF000, 0xF800)
            i += 4
        else:
            i += 2
    return bytes(out)


def place(sources, old, new):
    """Return {name: new_offset} for sources found consistently in `new`."""
    old_m, new_m = masked(old, CODE_LIMIT), masked(new, CODE_LIMIT)
    hits = {}
    for f in sources:
        start, size = f['rom_offset'], f['size']
        if start + size > CODE_LIMIT:
            data = old[start:start + size]
            found, j = [], new.find(data)
            while j >= 0 and len(found) < 4:
                found.append(j)
                j = new.find(data, j + 1)
        else:
            data, found, j = old_m[start:start + size], [], -1
            while True:
                j = new_m.find(data, j + 1)
                if j < 0:
                    break
                if j % 2 == 0:
                    found.append(j)
        hits[f['name']] = found
    # Unique long matches anchor the order; keep the longest increasing run.
    anchors = sorted((f['rom_offset'], hits[f['name']][0]) for f in sources
                     if len(hits[f['name']]) == 1 and f['size'] >= 24)
    tails, index, previous = [], [], [-1] * len(anchors)
    for k, (_, target) in enumerate(anchors):
        p = bisect.bisect_left(tails, target)
        if p == len(tails):
            tails.append(target)
            index.append(k)
        else:
            tails[p], index[p] = target, k
        previous[k] = index[p - 1] if p else -1
    keep, k = [], index[-1] if index else -1
    while k >= 0:
        keep.append(anchors[k])
        k = previous[k]
    keep.reverse()
    starts = [x[0] for x in keep]
    placed = {}
    for f in sources:
        start = f['rom_offset']
        p = bisect.bisect_right(starts, start)
        low = keep[p - 1] if p else (0, 0)
        high = keep[p] if p < len(keep) else (len(old), len(new))
        candidates = [j for j in hits[f['name']] if low[1] <= j <= high[1]]
        if len(candidates) > 1:
            expected = start + (low[1] - low[0])
            candidates = [min(candidates, key=lambda j: abs(j - expected))]
        if candidates:
            placed[f['name']] = candidates[0]
    return placed


def relocations(path, entry):
    with path.open('rb') as stream:
        elf = ELFFile(stream)
        symtab = elf.get_section_by_name('.symtab')
        for section in elf.iter_sections():
            if section['sh_type'] not in ('SHT_REL', 'SHT_RELA'):
                continue
            if elf.get_section(section['sh_info']).name != '.text':
                continue
            for r in section.iter_relocations():
                symbol = symtab.get_symbol(r['r_info_sym'])
                yield (r['r_offset'] + entry, r['r_info_type'], symbol.name,
                       symbol['st_shndx'] == 'SHN_UNDEF')


def compare(f, o0, o1, old, new, obj, moved, conditioned=False):
    """Check a placed extent differs only in relocation fields; solve symbols.

    `moved` is the change in execution address, which differs from the change
    in ROM storage offset for code copied to RAM.
    """
    size, mask, solved = f['size'], bytearray(f['size']), {}
    for offset, kind, name, external in relocations(obj, f.get('entry_offset', 0)):
        mask[offset:offset + 4] = b'\1\1\1\1'
        if kind == R_ARM_ABS32:
            delta = word(new, o1 + offset) - word(old, o0 + offset)
        elif kind == R_ARM_THM_CALL:
            delta = (thumb_bl_target(new, o1 + offset) - thumb_bl_target(old, o0 + offset)
                     - (o1 - o0) + moved)
        elif kind in R_ARM_CALLS:
            delta = (arm_bl_target(new, o1 + offset) - arm_bl_target(old, o0 + offset)
                     - (o1 - o0) + moved)
        else:
            return None, f'unsupported relocation type {kind}'
        if not external:
            if kind == R_ARM_ABS32 and delta != moved:
                return None, 'section-relative word moved inconsistently'
            continue
        value = f.get('symbols', {}).get(name)
        if value is None:
            return None, f'relocation symbol {name} has no manifest value'
        new_value = int(str(value), 0) + delta
        if solved.setdefault(name, new_value) != new_value:
            return None, f'relocation symbol {name} solved inconsistently'
    differing = [i for i in range(size) if not mask[i] and old[o0 + i] != new[o1 + i]]
    # Revision-conditioned sources select different constants; the pilot,
    # not this placement check, decides whether those bytes match.
    if differing and not conditioned:
        return None, f'{len(differing)} non-relocation bytes differ'
    return solved, None


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source-target', default='us-eu')
    parser.add_argument('--target', default='us-rev1')
    parser.add_argument('--pilot-run', help='Accepted source-target pilot run directory')
    parser.add_argument('--report', default=None)
    args = parser.parse_args()
    old_target = json.loads((ROOT / f'config/targets/{args.source_target}.json').read_text())
    new_target = json.loads((ROOT / f'config/targets/{args.target}.json').read_text())
    old, old_identity = audit(ROOT / old_target['rom_path'], old_target)
    new, new_identity = audit(ROOT / new_target['rom_path'], new_target)
    if not (old_identity['accepted'] and new_identity['accepted']):
        raise ValueError('Reference ROM identity check failed')
    manifest = json.loads((ROOT / f'config/build-{args.source_target}.json').read_text())
    ram = json.loads((ROOT / f'config/ram-map-{args.source_target}.json').read_text())
    pilot = json.loads((ROOT / f'reports/{args.source_target}/pilot.json').read_text())
    if not pilot['accepted']:
        raise ValueError('Source-target pilot run is not accepted')
    run = Path(args.pilot_run or pilot['output_directory'])
    port_path = ROOT / f'config/port-{args.target}.json'
    port = json.loads(port_path.read_text()) if port_path.exists() else {}
    conditioned = set(port.get('revision_conditioned', ()))
    sources = manifest['functions'] + manifest.get('assembly', [])
    placed = place(sources, old, new)

    copy_rejected = {}
    def translate_rom(offset):
        """Translate a ROM offset that lies inside a carried extent."""
        for f in sources:
            if f['name'] in placed and f['rom_offset'] <= offset < f['rom_offset'] + f['size']:
                return placed[f['name']] + offset - f['rom_offset']
        return None

    copies, copy_map = [], {}
    for copy in ram['copies']:
        item = {k: v for k, v in copy.items() if k != 'classification'}
        if 'startup_literal_offset' in copy:
            literals = [copy['startup_literal_offset']]
        elif 'word_copy_literal_offsets' in copy:
            literals = [translate_rom(o) for o in copy['word_copy_literal_offsets']]
            if None in literals:
                copy_rejected[copy['name']] = 'copy literals are outside placed source'
                continue
            item['word_copy_literal_offsets'] = literals
        else:
            literals = [translate_rom(copy.get('dma_literal_offset', 0x1f88c))]
            if None in literals:
                copy_rejected[copy['name']] = 'copy literals are outside placed source'
                continue
            item['dma_literal_offset'] = literals[0]
        base = literals[0]
        item['rom_offset'] = word(new, base) - ROM_BASE
        item['ram_address'] = word(new, base + 4)
        if 'startup_literal_offset' in copy:
            item['size'] = word(new, base + 8) - item['ram_address']
        elif 'word_copy_literal_offsets' in copy:
            item['word_copy_control'] = word(new, literals[2])
            item['size'] = (item['word_copy_control'] & 0x1fffff) * 4
        item['classification'] = (f"Derived from the {args.source_target} map at "
                                  f"ROM {copy['rom_offset']:#x}; see config/ram-map-"
                                  f"{args.source_target}.json for evidence.")
        copies.append(item)
        copy_map[copy['name']] = (copy, item)

    def translate_ram(address):
        for copy, item in copy_map.values():
            if copy['ram_address'] <= address < copy['ram_address'] + copy['size']:
                rom = translate_rom(copy['rom_offset'] + address - copy['ram_address'])
                if rom is not None and item['rom_offset'] <= rom < item['rom_offset'] + item['size']:
                    return item['ram_address'] + rom - item['rom_offset']
        return None

    carried, rejected, symbols = {}, dict(copy_rejected), collections.defaultdict(set)
    for f in sources:
        name = f['name']
        if name not in placed:
            rejected[name] = 'not found in target ROM'
            continue
        moved = placed[name] - f['rom_offset']
        if 'ram_address' in f:
            pair = copy_map.get(f['ram_copy'])
            if pair is None:
                rejected[name] = 'RAM copy could not be derived'
                continue
            moved = pair[1]['ram_address'] + placed[name] - pair[1]['rom_offset'] - f['ram_address']
        solved, reason = compare(f, f['rom_offset'], placed[name], old, new,
                                 run / name / 'source.o', moved, name in conditioned)
        if reason:
            rejected[name] = reason
            continue
        carried[name] = solved
        for key, value in solved.items():
            symbols[key].add(value)
    conflicts = {k: sorted(v) for k, v in symbols.items() if len(v) > 1}
    for name, solved in list(carried.items()):
        if any(k in conflicts for k in solved):
            rejected[name] = 'shares an inconsistently solved symbol'
            del carried[name]
    values = {k: next(iter(v)) for k, v in symbols.items() if k not in conflicts}

    entries = []
    for entry in ram['entries']:
        item = dict(entry)
        item['ram_address'] = translate_ram(entry['ram_address'])
        if 'pointer_rom_offset' in entry:
            item['pointer_rom_offset'] = translate_rom(entry['pointer_rom_offset'])
        if item['ram_address'] is None or item.get('pointer_rom_offset', 0) is None:
            continue
        item['evidence'] = f"Derived from {args.source_target}: {entry['evidence']}"
        entries.append(item)

    definitions = {}
    for f in sources:
        if f['name'] in carried and f.get('defines_symbol', True):
            if 'ram_address' in f:
                pair = copy_map[f['ram_copy']][1]
                address = pair['ram_address'] + placed[f['name']] - pair['rom_offset']
            else:
                address = ROM_BASE + placed[f['name']]
            definitions[f['name']] = address + f.get('entry_offset', 0)
    out_functions, out_assembly = [], []
    for f in sources:
        name = f['name']
        if name not in carried:
            continue
        item = dict(f)
        item['rom_offset'] = placed[name]
        # Unreferenced aliases cannot be solved from relocations; a carried
        # definition supplies them, otherwise they do not affect the bytes.
        item['symbols'] = {}
        for k, v in f.get('symbols', {}).items():
            if k in values:
                item['symbols'][k] = f"{values[k]:#010x}"
            elif k in definitions:
                old_value = int(str(v), 0)
                item['symbols'][k] = f"{definitions[k] | (old_value & 1):#010x}"
        if 'thumb_symbols' in f:
            item['thumb_symbols'] = [k for k in f['thumb_symbols']
                                     if k in item['symbols'] or k in definitions]
        if 'ram_address' in f:
            copy, new_copy = copy_map.get(f['ram_copy'], (None, None))
            if new_copy is None:
                rejected[name] = 'RAM copy could not be derived'
                continue
            item['ram_address'] = new_copy['ram_address'] + placed[name] - new_copy['rom_offset']
        if 'expected_sha256' in f:
            item['expected_sha256'] = hashlib.sha256(
                new[placed[name]:placed[name] + f['size']]).hexdigest()
        (out_assembly if f in manifest.get('assembly', []) else out_functions).append(item)

    # Sources whose code changed in this revision: placed by hand, with
    # symbols taken from the values solved for the rest of the target.
    for name, offset in port.get('placements', {}).items():
        placement = offset if isinstance(offset, dict) else {'rom_offset': offset}
        start = int(str(placement['rom_offset']), 0)
        f = next(f for f in sources if f['name'] == name)
        if 'ram_address' in f:
            new_copy = copy_map[f['ram_copy']][1]
            definitions[name] = new_copy['ram_address'] + start - new_copy['rom_offset']
        else:
            definitions[name] = ROM_BASE + start
    for name, offset in port.get('placements', {}).items():
        f = next(f for f in sources if f['name'] == name)
        if name in carried:
            raise ValueError(f'Placed function {name} was already carried')
        placement = offset if isinstance(offset, dict) else {'rom_offset': offset}
        item = {**f, 'rom_offset': int(str(placement['rom_offset']), 0),
                'size': placement.get('size', f['size']), 'symbols': {}}
        wanted = {**f.get('symbols', {}),
                  **{k: '0' for k in placement.get('extra_symbols', ())}}
        # Callees that no carried source calls are given explicitly.
        explicit = placement.get('symbol_values', {})
        for k, v in wanted.items():
            if k in explicit:
                item['symbols'][k] = explicit[k]
            elif k in values:
                item['symbols'][k] = f"{values[k]:#010x}"
            elif k in definitions:
                item['symbols'][k] = f"{definitions[k] | (int(str(v), 0) & 1):#010x}"
            else:
                raise ValueError(f'No {args.target} value for {k} used by {name}')
        if 'ram_address' in f:
            new_copy = copy_map[f['ram_copy']][1]
            item['ram_address'] = new_copy['ram_address'] + item['rom_offset'] - new_copy['rom_offset']
        if 'inline_glue_spans' in placement:
            item['inline_glue'] = {**f['inline_glue'], 'spans': placement['inline_glue_spans']}
        if 'expected_sha256' in f:
            item['expected_sha256'] = hashlib.sha256(
                new[item['rom_offset']:item['rom_offset'] + item['size']]).hexdigest()
        rejected.pop(name, None)
        out_functions.append(item)
    # Target-only sources, e.g. a routine rebuilt differently in this revision.
    for item in port.get('extra_functions', ()):
        if item['name'] in carried or any(f['name'] == item['name'] for f in out_functions):
            raise ValueError(f"Extra function {item['name']} duplicates a carried source")
        out_functions.append(dict(item))
    new_manifest = {**manifest, 'target': args.target,
                    'functions': out_functions, 'assembly': out_assembly}
    new_ram = {'target': args.target, 'copies': copies, 'entries': entries,
               'limitations': [f'Derived from config/ram-map-{args.source_target}.json '
                               'by tools/port_target.py; carries no independent evidence.']}
    (ROOT / f'config/build-{args.target}.json').write_text(json.dumps(new_manifest, indent=2) + '\n')
    (ROOT / f'config/ram-map-{args.target}.json').write_text(json.dumps(new_ram, indent=2) + '\n')
    report = {'source_target': args.source_target, 'target': args.target,
              'pilot_run': str(run), 'carried_functions': len(out_functions),
              'carried_assembly': len(out_assembly), 'rejected': rejected,
              'symbol_conflicts': {k: [hex(x) for x in v] for k, v in conflicts.items()}}
    path = Path(args.report) if args.report else ROOT / f'reports/{args.target}/port.json'
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(report, indent=2) + '\n')
    print(f"Carried {len(out_functions)} C functions and {len(out_assembly)} assembly "
          f"regions; {len(rejected)} rejected. Report: {path}")
    return 0


if __name__ == '__main__':
    sys.exit(main())
