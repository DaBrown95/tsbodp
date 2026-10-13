#include "save_stream.h"

void save_stream_read_bits(unsigned char *destination, unsigned int count)
{
    unsigned int remaining = count;
    unsigned char *output = destination;
    if (remaining != 0) {
        unsigned char **cursor = &g_save_bit_cursor.cursor;
        int *bit = &g_save_bit_cursor.bit_offset;
        do {
            *output = (**cursor >> *bit) & 1;
            if (++*bit > 7) {
                ++*cursor;
                *bit = 0;
            }
            ++output;
        } while (--remaining != 0);
    }
}
asm(".align 2, 0");
