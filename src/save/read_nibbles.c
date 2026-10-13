#include "save_stream.h"

static inline unsigned char save_stream_low_nibble(const unsigned char *byte)
{
    return *byte & 15;
}
void save_stream_read_nibbles(unsigned char *destination, unsigned int count)
{
    if ((g_save_stream_state.bit_offset & 3) > 0) {
        if (g_save_stream_state.bit_offset <= 3)
            g_save_stream_state.bit_offset = 4;
        else {
            ++g_save_stream_state.cursor;
            g_save_stream_state.bit_offset = 0;
        }
    }
    {
        unsigned char *output = destination;
        if (count != 0) {
            int *bit = &g_save_bit_cursor.bit_offset;
            /* The cursor word precedes the bit-position word in this view. */
            register unsigned char **cursor asm("r5") =
                (unsigned char **)((unsigned int)bit - 4);
            do {
                int next_bit;
                if (*bit == 0) {
                    *output = save_stream_low_nibble(*cursor);
                    next_bit = 4;
                } else {
                    unsigned char *byte = *cursor;
                    /* This scalar is scoped to the high-nibble extraction. */
                    register unsigned int value asm("r1") = *byte;
                    value >>= 4;
                    *output = value;
                    *cursor = byte + 1;
                    next_bit = 0;
                }
                *bit = next_bit;
                ++output;
            } while (--count != 0);
        }
    }
}
asm(".align 2, 0");
