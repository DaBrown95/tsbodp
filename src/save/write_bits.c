#include "save_stream.h"

void save_stream_write_bits(const unsigned char *source, unsigned int count)
{
    unsigned int remaining = count;
    const unsigned char *input = source;
    if (remaining != 0) {
        unsigned char **cursor = &g_save_bit_cursor.cursor;
        int *bit = &g_save_bit_cursor.bit_offset;
        do {
            **cursor &= 255 >> (8 - *bit);
            **cursor |= (*input & 1) << *bit;
            if (++*bit > 7) {
                ++*cursor;
                *bit = 0;
            }
            ++input;
        } while (--remaining != 0);
    }
}
asm(".align 2, 0");
