unsigned int display_find_tile_run(const unsigned char *bitmap, int count, unsigned int first)
{
    register unsigned int current __asm__("r12") = first;
    register unsigned int found __asm__("r5") = 0;
    register int remaining __asm__("r14") = 1;
    register int needed __asm__("r4") = count;
    while ((current + needed <= 1024) & (remaining > 0)) {
        int bits;
        unsigned int bit;
        found = current;
        remaining = needed;
        goto next_byte;
    next_bit:
        --remaining;
        ++bit;
        if ((bit <= 7) & (remaining > 0)) goto test_bit;
    next_byte:
        if (remaining <= 0) goto next_run;
        bits = bitmap[current >> 3];
        if (bits == 255) { current += 8; goto next_run; }
        if (!bits) { current += 8; remaining -= 8; goto next_byte; }
        bit = current & 7;
    test_bit:
        ++current;
        if (!((bits >> bit) & 1)) goto next_bit;
    next_run:;
    }
    if (remaining <= 0) return found; return 0xffff;
}
