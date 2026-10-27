"""Project verified source extents onto installations without inventing entries."""


def _interval(row, limit):
    start, size = row['rom_offset'], row['size']
    if (type(start) is not int or type(size) is not int or start < 0
            or size <= 0 or start + size > limit):
        raise ValueError('Copy/source extent is outside the ROM')
    return start, start + size


def _union_size(spans):
    total, end = 0, -1
    for lo, hi in sorted(spans):
        total += max(0, hi - max(lo, end))
        end = max(end, hi)
    return total


def project_copy_ownership(copies, verified, rom_size):
    """Call only after receipt verification; copied fragments grant no new credit."""
    if type(rom_size) is not int or rom_size <= 0:
        raise ValueError('Invalid ROM size')
    kinds = {'exact_c': 'compiled_c', 'exact_glue': 'assembly_glue'}
    owners, names, previous_end = [], set(), 0
    for row in sorted(verified, key=lambda r: r['rom_offset']):
        lo, hi = _interval(row, rom_size)
        if (row.get('status') not in kinds or not row.get('source')
                or not row.get('name') or row['name'] in names):
            raise ValueError('Only distinct verified source extents can own copies')
        if lo < previous_end:
            raise ValueError('Verified source extents overlap')
        names.add(row['name'])
        owners.append((lo, hi, row))
        previous_end = hi

    installations, names = [], set()
    physical = {kind: [] for kind in ('compiled_c', 'assembly_glue', 'without_verified_source')}
    for copy in copies:
        start, end = _interval(copy, rom_size)
        address = copy['ram_address']
        if (not copy.get('name') or copy['name'] in names
                or type(address) is not int or address < 0
                or address + end - start > 0x100000000):
            raise ValueError('Invalid or duplicate copy installation')
        names.add(copy['name'])
        segments, cursor = [], start

        def append(lo, hi, owner=None):
            kind = kinds[owner['status']] if owner else 'without_verified_source'
            segment = {'rom_offset': lo, 'ram_address': address + lo - start,
                       'size': hi - lo, 'source_kind': kind}
            if owner:
                segment.update({'source_extent_name': owner['name'],
                                'source': owner['source'],
                                'source_extent_rom_offset': owner['rom_offset'],
                                'source_extent_size': owner['size'],
                                'whole_source_extent': (lo == owner['rom_offset']
                                                        and hi - lo == owner['size'])})
            segments.append(segment)
            physical[kind].append((lo, hi))

        for lo, hi, owner in owners:
            if hi <= start:
                continue
            if lo >= end:
                break
            lo, hi = max(start, lo), min(end, hi)
            if cursor < lo:
                append(cursor, lo)
            append(lo, hi, owner)
            cursor = hi
        if cursor < end:
            append(cursor, end)
        counts = {kind: sum(s['size'] for s in segments if s['source_kind'] == kind)
                  for kind in physical}
        if sum(counts.values()) != copy['size']:
            raise ValueError('Copy source partition is incomplete')
        installations.append({'name': copy['name'], 'rom_offset': start,
                              'ram_address': address, 'size': end - start,
                              'counts': counts, 'segments': segments})

    unique = {kind: _union_size(spans) for kind, spans in physical.items()}
    unique_bytes = _union_size([_interval(c, rom_size) for c in copies])
    if sum(unique.values()) != unique_bytes:
        raise ValueError('Physical copy source ownership is inconsistent')
    installed = sum(c['size'] for c in installations)
    return {'scope': 'Physical intersections with receipt-verified source extents, '
                     'including their pools and alignment. Other bytes retain '
                     'their existing inventory classification. No new source credit, '
                     'runtime entry or complete function at a partial copied alias.',
            'installation_bytes': installed, 'unique_rom_bytes': unique_bytes,
            'duplicate_installation_bytes': installed - unique_bytes,
            'unique_rom_counts': unique, 'installations': installations}
