#!/usr/bin/env python3
"""Publish a treemap of verified source and bounded unconverted code extents."""
import argparse
from bisect import bisect_left
from datetime import datetime
import hashlib
import json
from pathlib import Path
from zoneinfo import ZoneInfo
from project import ROOT
from rom_layout import layout

COLORS = {'exact_c': '#00b800', 'unconverted': '#373a3e'}
BACKGROUND, FOREGROUND, MUTED = '#141619', '#f0f2f5', '#a5aeb8'


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def verify_functions(functions, receipts, source_hash):
    """Reject missing, stale or partial source evidence instead of coloring it green."""
    by_name = {r['name']: r for r in receipts}
    if len(by_name) != len(receipts) or set(by_name) != {f['name'] for f in functions}:
        raise ValueError('Source receipt inventory differs from the manifest')
    result = []
    for f in functions:
        r = by_name[f['name']]
        if (not r.get('identical') or not r.get('source_reconstruction_verified')
                or r['source_sha256'] != source_hash(f)
                or any(r[k] != f[k] for k in ('rom_offset', 'size'))
                or r['reference_size'] != f['size'] or r['candidate_size'] != f['size']):
            raise ValueError(f"Unverified or stale source: {f['name']}")
        result.append({**f, 'status': 'exact_c',
                       'group': 'Interrupts' if f.get('source', '').startswith('src/irq/')
                       or f['name'] == 'set_irq_table_entry' else 'Utilities'})
    return result


def inventory():
    manifest = json.loads((ROOT / 'pilot/manifest.json').read_text())
    regions = json.loads((ROOT / 'config/progress-regions-us-eu.json').read_text())
    pilot = json.loads((ROOT / 'reports/us-eu/pilot.json').read_text())
    build = json.loads((ROOT / 'reports/us-eu/build.json').read_text())
    target = json.loads((ROOT / 'config/targets/us-eu.json').read_text())
    if (not pilot['accepted'] or not build['accepted'] or not build['comparison']['identical']
            or not build['negative_control_rejected'] or pilot['run_id'] != build['run_id']
            or pilot['reference_sha256'] != target['sha256']
            or build['reference_sha256'] != target['sha256']):
        raise ValueError('Run make build before publishing progress')
    for report in (pilot, build):
        for name, digest in report['helper_sha256'].items():
            if sha(ROOT / name) != digest:
                raise ValueError(f'Stale helper proof: {name}; run make build')
    if sha(Path(build['output'])) != target['sha256']:
        raise ValueError('Retained linked ROM differs from verified identity')
    exact = verify_functions(manifest['functions'], pilot['functions'],
                             lambda f: sha(ROOT / f.get('source', 'pilot/candidates/' + f['name'] + '.c')))
    total_c = sum(f['size'] for f in exact)
    if (build['compiled_c_functions'] != len(exact)
            or build['compiled_c_bytes_including_pools_and_alignment'] != total_c
            or build['unconverted_bytes'] != target['size'] - total_c
            or build['regions'] != layout(manifest['functions'], target['size'])):
        raise ValueError('Source credit differs from full-ROM layout')
    # Remove retired grey regions only after a source replacement owns that
    # complete extent. Partial overlaps require an explicit map update.
    rows = list(exact)
    for r in regions['unconverted_extents']:
        start, end = r['rom_offset'], r['rom_offset'] + r['size']
        replacements = [f for f in exact if f['rom_offset'] < end and f['rom_offset'] + f['size'] > start]
        if replacements:
            if len(replacements) != 1 or replacements[0]['rom_offset'] != start or replacements[0]['size'] != r['size']:
                raise ValueError('Update the bounded map after a partial source replacement')
        else:
            rows.append({**r, 'status': 'unconverted'})
    layout(rows, target['size'])  # Every mapped extent must be disjoint.
    stamp = datetime.fromisoformat(build['recorded_at_utc'].replace('Z', '+00:00'))
    return {'target': 'us-eu', 'reference_sha256': target['sha256'],
            'verified_at': stamp.astimezone(ZoneInfo('Europe/London')).strftime('%d %b %Y, %H:%M %Z'),
            'compiled_c_functions': len(exact), 'compiled_c_bytes': total_c,
            'rom_bytes': target['size'], 'unconverted_rom_bytes': target['size'] - total_c,
            'whole_rom_identical': True, 'complete_code_inventory': False,
            'mapped_extent_bytes': sum(r['size'] for r in rows),
            'scope': regions['scope'],
            'rows': [{k: r[k] for k in ('name', 'group', 'rom_offset', 'size', 'status')} for r in rows],
            'input_sha256': {name: sha(ROOT / name) for name in
                             ('pilot/manifest.json', 'config/progress-regions-us-eu.json',
                              'tools/render_progress.py', 'config/progress-requirements.txt')}}


def binary_layout(items, box):
    """Partition by byte weight along the longest axis; no invented tiles."""
    items = sorted(items, key=lambda item: -item[1])
    if not items or any(value <= 0 for _, value in items):
        raise ValueError('Treemap weights must be positive')
    prefix = [0]
    for _, value in items:
        prefix.append(prefix[-1] + value)
    result = []

    def partition(lo, hi, x, y, width, height):
        if hi - lo == 1:
            result.append((items[lo][0], (x, y, width, height)))
            return
        split = bisect_left(prefix, (prefix[lo] + prefix[hi]) / 2, lo + 1, hi)
        fraction = (prefix[split] - prefix[lo]) / (prefix[hi] - prefix[lo])
        if width >= height:
            cut = width * fraction
            partition(lo, split, x, y, cut, height)
            partition(split, hi, x + cut, y, width - cut, height)
        else:
            cut = height * fraction
            partition(lo, split, x, y, width, cut)
            partition(split, hi, x, y + cut, width, height - cut)
    partition(0, len(items), *box)
    return result


def render(data, output):
    from PIL import Image, ImageDraw, ImageFont
    image = Image.new('RGB', (1600, 900), BACKGROUND)
    draw = ImageDraw.Draw(image)

    def font(size):
        for p in ('/System/Library/Fonts/Supplemental/Arial.ttf',
                  '/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf'):
            if Path(p).is_file():
                return ImageFont.truetype(p, size)
        return ImageFont.load_default(size=size)

    title, heading, body, small = (font(s) for s in (28, 18, 16, 13))
    draw.text((24, 18), "The Sims: Bustin' Out — Matching Progress", fill=FOREGROUND, font=title)
    draw.text((24, 58), 'USA / Europe  ·  Established code extents  ·  Inventory incomplete', fill=MUTED, font=body)
    x = 24
    for label, color in (('Exact C', COLORS['exact_c']), ('Unconverted mapped code', COLORS['unconverted'])):
        draw.rectangle((x, 92, x + 12, 104), fill=color)
        draw.text((x + 21, 88), label, fill=FOREGROUND, font=body)
        x += 21 + draw.textlength(label, font=body) + 34
    draw.text((24, 122), f"{data['compiled_c_functions']} matching C functions  ·  {data['compiled_c_bytes']:,} bytes including pools and alignment", fill=FOREGROUND, font=heading)
    groups = []
    for name in ('Interrupts', 'Startup and runtime', 'Utilities'):
        members = [r for r in data['rows'] if r['group'] == name]
        if members:
            groups.append(({'name': name, 'rows': members}, sum(r['size'] for r in members)))
    if sum(len(g['rows']) for g, _ in groups) != len(data['rows']):
        raise ValueError('Unhandled treemap group')
    for group, (x, y, w, h) in binary_layout(groups, (24, 163, 1552, 528)):
        draw.text((round(x + 6), round(y + 3)), group['name'], fill=FOREGROUND, font=heading)
        for r, (rx, ry, rw, rh) in binary_layout([(r, r['size']) for r in group['rows']], (x + 3, y + 33, w - 6, h - 37)):
            draw.rectangle((round(rx), round(ry), round(rx + rw) - 2, round(ry + rh) - 2), fill=COLORS[r['status']])
            if rw > 94 and rh > 40:
                label = r['name'].replace('_', ' ')
                if draw.textlength(label, font=small) > rw - 14:
                    while label and draw.textlength(label + '…', font=small) > rw - 14:
                        label = label[:-1]
                    label += '…'
                color = '#071307' if r['status'] == 'exact_c' else FOREGROUND
                draw.text((round(rx + 7), round(ry + 6)), label, fill=color, font=small)
                detail = f"{0x08000000+r['rom_offset']:08X}  ·  {r['size']} B"
                if draw.textlength(detail, font=small) > rw - 14:
                    detail = f"{r['size']} bytes"
                if draw.textlength(detail, font=small) <= rw - 14:
                    draw.text((round(rx + 7), round(ry + 24)), detail, fill=color, font=small)
    draw.text((24, 710), 'Tile area follows recorded byte length. Unmapped code and assets are outside this treemap.', fill=MUTED, font=body)
    draw.text((24, 750), 'Complete ROM: identical to reference  ·  Source reconstruction: incomplete', fill=FOREGROUND, font=heading)
    draw.text((24, 784), f"{data['compiled_c_bytes']:,} reconstructed bytes  /  {data['rom_bytes']:,} total ROM bytes  ·  {data['unconverted_rom_bytes']:,} remain unconverted", fill=MUTED, font=body)
    draw.text((24, 819), 'Audio RAM image: mapped entries and instruction writes; complete function boundaries pending.', fill=MUTED, font=body)
    draw.text((24, 866), 'Verified build: ' + data['verified_at'], fill=MUTED, font=small)
    output.parent.mkdir(parents=True, exist_ok=True)
    image.save(output, format='PNG', compress_level=6)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'assets/progress.png')
    args = parser.parse_args()
    data = inventory()
    render(data, args.output)
    args.output.with_suffix('.json').write_text(json.dumps(data, indent=2) + '\n')
    print(f"Progress treemap: {len(data['rows'])} mapped extents; {data['compiled_c_functions']} exact C functions")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
