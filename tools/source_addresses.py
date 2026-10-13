"""Validate source execution addresses separately from ROM storage extents."""

ROM_BASE = 0x08000000


def execution_address(function, copies=(), entries=()):
    mode = function.get('mode', 'Thumb')
    if mode not in ('Thumb', 'ARM'):
        raise ValueError('Unsupported C instruction mode')
    offset, size = function['rom_offset'], function['size']
    if not isinstance(offset, int) or not isinstance(size, int) or offset < 0 or size <= 0:
        raise ValueError('Invalid source storage extent')
    address = function.get('ram_address', ROM_BASE + offset)
    alignment = 4 if mode == 'ARM' else 2
    if not isinstance(address, int) or address % alignment or offset % alignment:
        raise ValueError('Source address is not aligned for its instruction mode')
    if 'ram_address' in function:
        matches = [copy for copy in copies if copy['name'] == function.get('ram_copy')]
        if len(matches) != 1:
            raise ValueError('Copied source needs one named installation map')
        copy = matches[0]
        delta = offset - copy['rom_offset']
        if (delta < 0 or delta + size > copy['size'] or
                address != copy['ram_address'] + delta):
            raise ValueError('Source execution address or extent differs from its RAM copy')
        if not any(lo <= address and address + size <= hi for lo, hi in
                   ((0x02000000, 0x02040000), (0x03000000, 0x03008000))):
            raise ValueError('Copied source lies outside GBA work RAM')
    elif 'ram_copy' in function:
        raise ValueError('RAM copy name requires an execution address')
    if any(entry['ram_address'] == address and entry['mode'] != mode for entry in entries):
        raise ValueError('Source instruction mode differs from its observed RAM entry')
    return address


def validate_execution_layout(functions, copies=(), entries=()):
    ranges = sorted((execution_address(f, copies, entries), f['size']) for f in functions)
    for (start, size), (next_start, _) in zip(ranges, ranges[1:]):
        if start + size > next_start:
            raise ValueError('Compiled source execution extents overlap')


def validate_symbol_definitions(manifest, copies=(), entries=()):
    """An external alias must agree with a definition that supersedes it."""
    sources = manifest['functions'] + manifest.get('assembly', [])
    definitions = {}
    for function in sources:
        if function.get('defines_symbol', True):
            name = function['name']
            if name in definitions:
                raise ValueError('Duplicate source symbol definition')
            definitions[name] = (execution_address(function, copies, entries),
                                 function.get('mode', 'Thumb'))
    for source in sources:
        thumb_symbols = set(source.get('thumb_symbols', ()))
        for name, value in source.get('symbols', {}).items():
            if name not in definitions:
                continue
            address, mode = definitions[name]
            declared = int(str(value), 0)
            if mode == 'Thumb':
                # Direct branch aliases may omit the mode bit. Explicit Thumb
                # declarations and pointers retain it; compare the code address.
                matches = (declared & ~1) == address
                if name in thumb_symbols and not declared & 1:
                    raise ValueError('Thumb definition alias is missing its mode bit')
            else:
                matches = declared == address
                if name in thumb_symbols:
                    raise ValueError('Thumb alias refers to an ARM definition')
            if not matches:
                raise ValueError(f'External symbol {name} differs from its source execution address')
