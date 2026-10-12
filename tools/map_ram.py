#!/usr/bin/env python3
"""Verify copied-region addresses and export local RAM images for analysis."""
import hashlib
import json
import struct
from project import ROOT, audit, write_report


def main():
    target = json.loads((ROOT / 'config/targets/us-eu.json').read_text())
    rom, identity = audit(ROOT / target['rom_path'], target)
    if not identity['accepted']:
        return 1
    mapping = json.loads((ROOT / 'config/ram-map-us-eu.json').read_text())
    word = lambda offset: struct.unpack_from('<I', rom, offset)[0]
    folder = ROOT / 'analysis/us-eu/ram'
    folder.mkdir(parents=True, exist_ok=True)
    copies = []
    for copy in mapping['copies']:
        start, address, size = copy['rom_offset'], copy['ram_address'], copy['size']
        if 'startup_literal_offset' in copy:
            off = copy['startup_literal_offset']
            if [word(off), word(off + 4), word(off + 8)] != [0x08000000 + start, address, address + size]:
                raise ValueError('Startup copy literals do not match map')
        else:
            if [word(o) for o in (0x1f88c, 0x1f890, 0x1f894)] != [0x08000000 + start, address, 0x84000080]:
                raise ValueError('IRQ DMA literals differ')
            if size != 128 * 4:
                raise ValueError('DMA word count differs')
        data = rom[start:start + size]
        if len(data) != size:
            raise ValueError('Truncated copy')
        nonzero = [i for i, value in enumerate(data) if value]
        path = folder / copy['exports']
        path.write_bytes(data)
        copies.append({**copy, 'sha256': hashlib.sha256(data).hexdigest(),
                       'nonzero_bytes': len(nonzero), 'last_nonzero_offset': nonzero[-1] if nonzero else None,
                       'trailing_zero_bytes': size - nonzero[-1] - 1 if nonzero else size,
                       'nonzero_locations_if_sparse': nonzero if len(nonzero) < 16 else None,
                       'local_export': str(path)})
    entries = []
    for entry in mapping['entries']:
        address = entry['ram_address']
        if 'pointer_rom_offset' in entry and word(entry['pointer_rom_offset']) != address:
            raise ValueError('RAM entry pointer differs')
        owners = [c for c in copies if c['ram_address'] <= address < c['ram_address'] + c['size']]
        if len(owners) != 1:
            raise ValueError('RAM entry has ambiguous or absent mapping')
        owner = owners[0]
        entries.append({**entry, 'rom_offset': owner['rom_offset'] + address - owner['ram_address']})
    defaults = [word(mapping['irq_default_table_rom_offset'] + i * 4) for i in range(13)]
    if defaults[3] != 0x03000004:
        raise ValueError('Audio IRQ entry differs')
    report = {**mapping, 'copies': copies, 'entries': entries, 'irq_default_entries': defaults,
              'reference_sha256': identity['sha256'], 'accepted': True,
              'helper_sha256': hashlib.sha256((ROOT / 'tools/map_ram.py').read_bytes()).hexdigest(),
              'map_sha256': hashlib.sha256((ROOT / 'config/ram-map-us-eu.json').read_bytes()).hexdigest()}
    (folder / 'map.json').write_text(json.dumps(report, indent=2) + '\n')
    write_report('ram-map', report)
    for c in copies:
        print(f"{c['name']}: ROM {0x08000000+c['rom_offset']:#010x} -> "
              f"RAM {c['ram_address']:#010x}, {c['size']} bytes; {c['classification']}")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
