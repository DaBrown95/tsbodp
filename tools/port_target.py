#!/usr/bin/env python3
"""Carry matched functions from one target's build manifest into another's.

Each target keeps its own hand-maintained manifest (config/<target>/build.json)
and RAM map; this tool only proposes additions. A function from the source
manifest that the destination does not list yet is added when its compiled
bytes, with relocation fields masked, occur in the destination ROM at a
position consistent with its neighbours and differ only in relocation fields.
Symbol values are solved from those fields and must agree with the values the
destination already uses. Entries already in the destination are never
changed, so revision-specific placements stay as written.

Inputs are both pinned reference ROMs and the object files of the source
target's latest accepted pilot run. Nothing here grants source credit: every
addition must still pass the destination's pilot, whole-ROM and changed-source
gates (`make build TARGET=<destination>`).
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
from project import ROOT, TARGETS, audit, load_target, target_paths

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


def compare(f, o0, o1, old, new, obj, moved):
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
    if differing:
        return None, f'{len(differing)} non-relocation bytes differ'
    return solved, None


def execution_address(f):
    """Address the function runs at: its RAM copy address, else its ROM address."""
    if 'ram_address' in f:
        return f['ram_address']
    return ROM_BASE + f['rom_offset']


def carry(source, destination, copy_pairs, placed, check):
    """Return (additions, rejected) for source functions missing from destination.

    `copy_pairs` maps RAM copy names to (source copy, destination copy);
    `placed` maps function names to destination ROM offsets; `check(f, offset,
    moved)` returns (solved symbols, reason) as `compare` does.
    """
    existing = {f['name'] for f in destination['functions'] + destination.get('assembly', [])}
    known = {}
    for f in destination['functions'] + destination.get('assembly', []):
        for k, v in f.get('symbols', {}).items():
            known.setdefault(k, int(str(v), 0))
    definitions = {f['name']: execution_address(f) + f.get('entry_offset', 0)
                   for f in destination['functions'] + destination.get('assembly', [])
                   if f.get('defines_symbol', True)}
    rejected, carried = {}, {}
    assembly = {f['name'] for f in source.get('assembly', [])}
    candidates = [f for f in source['functions'] + source.get('assembly', [])
                  if f['name'] not in existing]
    for f in candidates:
        name = f['name']
        if name not in placed:
            rejected[name] = 'not found in destination ROM'
            continue
        moved = placed[name] - f['rom_offset']
        new_ram = None
        if 'ram_address' in f:
            pair = copy_pairs.get(f['ram_copy'])
            if pair is None:
                rejected[name] = 'destination RAM map has no matching copy'
                continue
            new_ram = pair[1]['ram_address'] + placed[name] - pair[1]['rom_offset']
            moved = new_ram - f['ram_address']
        solved, reason = check(f, placed[name], moved)
        if reason:
            rejected[name] = reason
            continue
        clash = [k for k, v in solved.items() if known.get(k, v) != v]
        if clash:
            rejected[name] = f'symbol {clash[0]} disagrees with the destination manifest'
            continue
        carried[name] = (f, solved, new_ram)
    # Symbols solved two ways by different carried functions are unreliable.
    values = collections.defaultdict(set)
    for _, solved, _ in carried.values():
        for k, v in solved.items():
            values[k].add(v)
    conflicts = {k for k, v in values.items() if len(v) > 1}
    for name in [n for n, (_, solved, _) in carried.items() if conflicts & set(solved)]:
        rejected[name] = 'shares an inconsistently solved symbol'
        del carried[name]
    solved_values = {**known, **{k: next(iter(v)) for k, v in values.items() if k not in conflicts}}
    for name, (f, _, new_ram) in carried.items():
        if f.get('defines_symbol', True):
            address = new_ram if new_ram is not None else ROM_BASE + placed[name]
            definitions[name] = address + f.get('entry_offset', 0)
    additions = {'functions': [], 'assembly': []}
    for name, (f, _, new_ram) in carried.items():
        item = {**f, 'rom_offset': placed[name], 'symbols': {}}
        # Unreferenced aliases cannot be solved from relocations; a known
        # definition supplies them, otherwise they do not affect the bytes.
        for k, v in f.get('symbols', {}).items():
            if k in solved_values:
                item['symbols'][k] = f"{solved_values[k]:#010x}"
            elif k in definitions:
                item['symbols'][k] = f"{definitions[k] | (int(str(v), 0) & 1):#010x}"
        if 'thumb_symbols' in f:
            item['thumb_symbols'] = [k for k in f['thumb_symbols']
                                     if k in item['symbols'] or k in definitions]
        if new_ram is not None:
            item['ram_address'] = new_ram
        additions['assembly' if name in assembly else 'functions'].append(item)
    return additions, rejected


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--from', dest='source', default='rev0', choices=TARGETS)
    parser.add_argument('--to', dest='destination', default='rev1', choices=TARGETS)
    parser.add_argument('--pilot-run', help='Accepted source-target pilot run directory')
    parser.add_argument('--dry-run', action='store_true', help='Report without writing the manifest')
    args = parser.parse_args()
    if args.source == args.destination:
        parser.error('--from and --to must differ')
    src, dst = target_paths(args.source), target_paths(args.destination)
    old_target, new_target = load_target(args.source), load_target(args.destination)
    old, old_identity = audit(ROOT / old_target['rom_path'], old_target)
    new, new_identity = audit(ROOT / new_target['rom_path'], new_target)
    if not (old_identity['accepted'] and new_identity['accepted']):
        raise ValueError('Reference ROM identity check failed')
    source = json.loads(src.manifest.read_text())
    destination = json.loads(dst.manifest.read_text())
    old_ram = json.loads(src.ram_map.read_text())
    new_ram = {c['name']: c for c in json.loads(dst.ram_map.read_text())['copies']}
    copy_pairs = {c['name']: (c, new_ram[c['name']]) for c in old_ram['copies'] if c['name'] in new_ram}
    pilot = json.loads((src.reports / 'pilot.json').read_text())
    if not pilot['accepted']:
        raise ValueError(f'The {args.source} pilot run is not accepted; run make pilot first')
    run = Path(args.pilot_run or pilot['output_directory'])
    placed = place(source['functions'] + source.get('assembly', []), old, new)

    def check(f, offset, moved):
        return compare(f, f['rom_offset'], offset, old, new, run / f['name'] / 'source.o', moved)

    additions, rejected = carry(source, destination, copy_pairs, placed, check)
    for key in ('functions', 'assembly'):
        for item in additions[key]:
            if 'expected_sha256' in item:
                item['expected_sha256'] = hashlib.sha256(
                    new[item['rom_offset']:item['rom_offset'] + item['size']]).hexdigest()
        destination[key] = destination.get(key, []) + additions[key]
    if not args.dry_run:
        dst.manifest.write_text(json.dumps(destination, indent=2) + '\n')
    report = {'from': args.source, 'to': args.destination, 'pilot_run': str(run),
              'added_functions': [f['name'] for f in additions['functions']],
              'added_assembly': [f['name'] for f in additions['assembly']],
              'not_carried': rejected, 'written': not args.dry_run}
    dst.reports.mkdir(parents=True, exist_ok=True)
    path = dst.reports / 'port.json'
    path.write_text(json.dumps(report, indent=2) + '\n')
    print(f"Added {len(additions['functions'])} C functions and {len(additions['assembly'])} "
          f"assembly regions to {dst.relative(dst.manifest)}; {len(rejected)} not carried. "
          f"Report: {path}")
    return 0


if __name__ == '__main__':
    sys.exit(main())
