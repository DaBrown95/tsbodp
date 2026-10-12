"""Explicit external function modes for source links; data is never inferred."""

LEGACY_THUMB = {'irq_noop', 'frame_update', '_call_via_r0'}


def declarations(symbols, thumb_symbols=()):
    thumb = set(thumb_symbols)
    if not thumb <= symbols.keys():
        raise ValueError('Thumb declaration has no external address')
    result = []
    for name, value in symbols.items():
        result.append(f'.global {name}')
        if name in thumb or name in LEGACY_THUMB:
            if not int(str(value), 0) & 1:
                raise ValueError('Thumb function address must retain its mode bit')
            result += [f'.type {name}, %function', f'.thumb_set {name}, {value}']
        else:
            result.append(f'.set {name}, {value}')
    return result
