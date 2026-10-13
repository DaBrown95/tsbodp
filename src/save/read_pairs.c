#include "save_stream.h"

void save_stream_read_pairs(unsigned char *destination, unsigned int count)
{
    if ((g_save_stream_state.bit_offset & 1) > 0) {
        if (g_save_stream_state.bit_offset <= 6)
            ++g_save_stream_state.bit_offset;
        else {
            ++g_save_stream_state.cursor;
            g_save_stream_state.bit_offset = 0;
        }
    }
    {
        unsigned char *output = destination;
        if (count != 0) {
            unsigned char **cursor = &g_save_bit_cursor.cursor;
            int *bit = &g_save_bit_cursor.bit_offset;
            do {
                *output = (**cursor >> *bit) & 3;
                *bit += 2;
                if (*bit > 7) {
                    ++*cursor;
                    *bit = 0;
                }
                ++output;
            } while (--count != 0);
        }
    }
}
asm(".align 2, 0");
