"""Separate compiled C from explicitly marked inline hardware glue."""
import re


MARKER_PREFIX = '__tsbodp_glue_'


def inline_glue(function):
    spec = function.get('inline_glue')
    if spec is None:
        return []
    if function.get('kind', 'compiled_c') != 'compiled_c':
        raise ValueError('Inline glue belongs to a compiled C extent')
    source = spec.get('source', '')
    if (not re.fullmatch(r'include/[A-Za-z0-9_/-]+\.h', source)
            or '..' in source.split('/')):
        raise ValueError('Inline glue header must be a project header')
    prefixes = [spec.get(key, '') for key in ('begin_prefix', 'end_prefix')]
    if (any(not re.fullmatch(MARKER_PREFIX + r'[A-Za-z0-9_]+', p) for p in prefixes)
            or prefixes[0].startswith(prefixes[1]) or prefixes[1].startswith(prefixes[0])):
        raise ValueError('Inline glue marker prefixes must be distinct and reserved')
    spans = spec.get('spans', [])
    width = 4 if function.get('mode', 'Thumb') == 'ARM' else 2
    cursor, total = 0, 0
    if not spans:
        raise ValueError('Inline glue requires explicit byte spans')
    for span in spans:
        offset, size = span.get('offset'), span.get('size')
        if (type(offset) is not int or type(size) is not int or size <= 0
                or offset < cursor or offset % width or size % width
                or offset + size > function['size']):
            raise ValueError('Inline glue spans are invalid, overlapping or outside the function')
        cursor, total = offset + size, total + size
    if total >= function['size']:
        raise ValueError('Inline glue cannot claim an entire C function')
    return spans


def byte_counts(function):
    if function.get('kind', 'compiled_c') == 'assembly_glue':
        if function.get('inline_glue') is not None:
            inline_glue(function)
        return 0, function['size']
    glue = sum(s['size'] for s in inline_glue(function))
    return function['size'] - glue, glue


def verify_inline_glue_symbols(function, symbols, address):
    """Labels emit no bytes; their linked addresses must prove the declared spans."""
    spans = inline_glue(function)
    marked = {name: value for name, value in symbols.items() if name.startswith(MARKER_PREFIX)}
    if not spans:
        if marked:
            raise ValueError('Compiled inline glue is missing its coverage declaration')
        return
    spec = function['inline_glue']
    begin, end = spec['begin_prefix'], spec['end_prefix']
    pairs = {}
    for name, value in marked.items():
        prefix = next((p for p in (begin, end) if name.startswith(p)), None)
        if prefix is None:
            raise ValueError('Unclaimed inline glue marker')
        suffix = name[len(prefix):]
        if not suffix or not suffix.isdigit():
            raise ValueError('Malformed inline glue marker')
        pairs.setdefault(suffix, {})[prefix] = value
    actual = []
    for pair in pairs.values():
        if set(pair) != {begin, end}:
            raise ValueError('Unpaired inline glue marker')
        actual.append({'offset': pair[begin] - address, 'size': pair[end] - pair[begin]})
    if sorted(actual, key=lambda s: s['offset']) != spans:
        raise ValueError('Linked inline glue spans differ from declared coverage')


def coverage_rows(function):
    """Split the verified extent so no inline hardware assembly is colored as C."""
    spans = inline_glue(function)
    if not spans:
        return [function]
    rows, cursor = [], 0
    for index, span in enumerate(spans, 1):
        if cursor < span['offset']:
            rows.append({**function, 'name': f"{function['name']}_c_{index}",
                         'rom_offset': function['rom_offset'] + cursor,
                         'size': span['offset'] - cursor, 'status': 'exact_c'})
        rows.append({**function, 'name': f"{function['name']}_glue_{index}",
                     'rom_offset': function['rom_offset'] + span['offset'],
                     'size': span['size'], 'status': 'exact_glue'})
        cursor = span['offset'] + span['size']
    if cursor < function['size']:
        rows.append({**function, 'name': f"{function['name']}_c_{len(spans)+1}",
                     'rom_offset': function['rom_offset'] + cursor,
                     'size': function['size'] - cursor, 'status': 'exact_c'})
    return rows
