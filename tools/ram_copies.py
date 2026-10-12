"""Validate fixed copy-installation literals without executing the ROM."""


def validate_copy(copy, word):
    start, address, size = copy['rom_offset'], copy['ram_address'], copy['size']
    if size <= 0:
        raise ValueError('RAM copy size must be positive')
    if 'startup_literal_offset' in copy:
        off = copy['startup_literal_offset']
        actual = [word(off + i) for i in (0, 4, 8)]
        expected = [0x08000000 + start, address, address + size]
    elif 'word_copy_literal_offsets' in copy:
        control = copy['word_copy_control']
        if control & ~0x041fffff or not control & 0x04000000 or size != (control & 0x1fffff) * 4:
            raise ValueError('Word-copy mode or byte count differs from map')
        actual = [word(off) for off in copy['word_copy_literal_offsets']]
        expected = [0x08000000 + start, address, control]
    else:
        actual = [word(off) for off in (0x1f88c, 0x1f890, 0x1f894)]
        expected = [0x08000000 + start, address, 0x84000080]
        if size != 512:
            raise ValueError('IRQ DMA word count differs from map')
    if actual != expected:
        raise ValueError('RAM copy literals differ from map')
