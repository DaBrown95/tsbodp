"""Pure interval accounting; discovery never grants matching-source credit."""

def partition(rows, size):
    """A complete, disjoint ROM accounting, including every unresolved byte."""
    result, cursor = [], 0
    for row in sorted(rows, key=lambda r: r['rom_offset']):
        start, end = row['rom_offset'], row['rom_offset'] + row['size']
        if start < cursor or end > size or row['size'] <= 0:
            raise ValueError('Invalid or overlapping inventory extent')
        if start > cursor:
            result.append({'name': f'Unresolved_{cursor:06X}', 'rom_offset': cursor,
                           'size': start-cursor, 'status': 'unresolved'})
        result.append({k: row[k] for k in ('name', 'rom_offset', 'size', 'status')})
        cursor = end
    if cursor < size:
        result.append({'name': f'Unresolved_{cursor:06X}', 'rom_offset': cursor,
                       'size': size-cursor, 'status': 'unresolved'})
    return result


def overlay(rows, exact):
    """Replace only independently verified source intervals; keep disjoint remnants."""
    result = list(exact)
    for row in rows:
        spans = [(row['rom_offset'], row['rom_offset'] + row['size'])]
        for source in exact:
            start, end = source['rom_offset'], source['rom_offset'] + source['size']
            clipped = []
            for lo, hi in spans:
                if hi <= start or lo >= end:
                    clipped.append((lo, hi))
                else:
                    if lo < start:
                        clipped.append((lo, start))
                    if hi > end:
                        clipped.append((end, hi))
            spans = clipped
        for lo, hi in spans:
            name = row['name'] if (lo, hi) == (row['rom_offset'], row['rom_offset']+row['size']) else f"{row['name']}_extent_{lo:06X}"
            result.append({**row, 'name': name, 'rom_offset': lo, 'size': hi-lo})
    return sorted(result, key=lambda r: r['rom_offset'])


def verify_discovery(data, size, reference_sha256):
    """The scanner can describe candidates/code, but cannot award source credit."""
    if (data['reference_sha256'] != reference_sha256 or data['rom_bytes'] != size
            or not data['complete_rom_partition'] or data['complete_code_inventory']):
        raise ValueError('Unsupported inventory identity or completeness claim')
    if any(row['status'] not in ('candidate', 'mapped_code') for row in data['rows']):
        raise ValueError('Discovery inventory cannot claim matching source')
    if any(row['status'] != 'mapped_data' for row in data.get('data_regions', [])):
        raise ValueError('Data regions cannot claim matching source')
    if data.get('inventory_schema_version') == 2:
        from inventory_census import verify_census
        if data.get('historical_mapped_extent_baseline') != 319640:
            raise ValueError('Historical comparison baseline changed')
        verify_census(data['code_census'], size)
    if (partition(data['rows']+data.get('data_regions', []), size) != data['partition']
            or data.get('extent_count', len(data['rows'])) != len(data['rows'])
            or data['entry_count'] != len({r.get('entry_rom_offset', r['rom_offset']) for r in data['rows']})
            or data['mapped_extent_bytes'] != sum(r['size'] for r in data['rows'])):
        raise ValueError('Inventory coverage/counts differ from recorded extents')
