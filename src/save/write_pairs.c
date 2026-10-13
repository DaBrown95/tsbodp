#include "save_stream.h"

void save_stream_write_pairs(const unsigned char *source, unsigned int count)
{
    if ((g_save_stream_state.bit_offset & 1) > 0) {
        *g_save_stream_state.cursor &= 255 >> (8 - g_save_stream_state.bit_offset);
        if (g_save_stream_state.bit_offset <= 6)
            ++g_save_stream_state.bit_offset;
        else {
            ++g_save_stream_state.cursor;
            g_save_stream_state.bit_offset = 0;
        }
    }
    {
        const unsigned char *input = source;
        if (count != 0) {
            unsigned char **cursor = &g_save_bit_cursor.cursor;
            int *bit = &g_save_bit_cursor.bit_offset;
            do {
                **cursor &= 255 >> (8 - *bit);
                **cursor |= (*input & 3) << *bit;
                *bit += 2;
                if (*bit > 7) {
                    ++*cursor;
                    *bit = 0;
                }
                ++input;
            } while (--count != 0);
        }
    }
}
asm(".align 2, 0");
