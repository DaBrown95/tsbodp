/*
 * Independent C reconstruction of the byte-clear provider used by player start.
 * The bzero loop in the pinned AGBCC libc corroborates the operation; its
 * Makefile selects old_agbcc -O2 -fno-builtin. No upstream source is copied.
 * Source: pret/agbcc, revision da598c1d918402c42c0c0d7128ba14567f3175e9,
 * libc/string/bzero.c and libc/Makefile.
 * The explicit previous value retains the observed postdecrement lifetime.
 */
void audio_zero_bytes(void *destination, unsigned int bytes)
{
    unsigned char *out = destination;

    for (;;) {
        unsigned int previous = bytes--;
        if (!previous)
            break;
        *out++ = 0;
    }
}
asm(".align 2, 0");
