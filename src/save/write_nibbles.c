#include "save_stream.h"

void save_stream_write_nibbles(const unsigned char *source, unsigned int length)
{
    unsigned int count;
    register const unsigned char *start asm("r6");
    start = source;
    count = length;
    if ((g_save_stream_state.bit_offset & 3) > 0) {
        *g_save_stream_state.cursor &= 255 >> (8 - g_save_stream_state.bit_offset);
        if (g_save_stream_state.bit_offset <= 3)
            g_save_stream_state.bit_offset = 4;
        else {
            ++g_save_stream_state.cursor;
            g_save_stream_state.bit_offset = 0;
        }
    }
    {
        unsigned int remaining;
        register const unsigned char *input asm("r4") = start;
        remaining = count;
        if (remaining != 0) {
            register int *bit asm("r6");
            unsigned char **cursor;
            register unsigned int mask asm("r12");
            bit = &g_save_bit_cursor.bit_offset;
            cursor = (unsigned char **)((unsigned int)bit - 4);
            mask = 15;
            do {
                int next_bit;
                if (*bit == 0) {
                    unsigned char *destination;
                    register unsigned int value asm("r1");
                    destination = *cursor;
                    value = *input;
                    *destination = mask & value;
                    next_bit = 4;
                } else {
                    unsigned char *destination;
                    unsigned int input_value, low;
                    register unsigned int saved asm("r2");
                    register unsigned int high asm("r1");
                    destination = *cursor;
                    input_value = *input;
                    high = mask;
                    high &= input_value;
                    high <<= 4;
                    saved = *destination;
                    low = mask;
                    low &= saved;
                    *destination = high + low;
                    ++*cursor;
                    next_bit = 0;
                }
                *bit = next_bit;
                ++input;
            } while (--remaining != 0);
        }
    }
}
asm(".align 2, 0");
