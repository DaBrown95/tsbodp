"""Check that source extents lie inside the ROM, do not overlap and do not hide unconverted bytes.

Needs neither a ROM nor a toolchain.
"""

def layout(functions, size):
    ordered = sorted(functions, key=lambda f: f['rom_offset'])
    cursor = 0
    result = []
    names = set()
    for f in ordered:
        start, length = f['rom_offset'], f['size']
        kind = f.get('kind', 'compiled_c')
        if kind not in ('compiled_c', 'assembly_glue'):
            raise ValueError('Unsupported source coverage kind')
        if f['name'] in names or length <= 0 or start < cursor or start + length > size:
            raise ValueError('Duplicate, overlapping, invalid or out-of-ROM source extent')
        names.add(f['name'])
        if start > cursor:
            result.append({'kind': 'unconverted', 'offset': cursor, 'size': start - cursor})
        result.append({'kind': kind, 'offset': start, 'size': length, 'name': f['name']})
        cursor = start + length
    if cursor < size:
        result.append({'kind': 'unconverted', 'offset': cursor, 'size': size - cursor})
    return result
