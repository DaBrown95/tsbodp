#include "frame_random.h"

short frame_random_signed_offset(unsigned short limit)
{
    int radius = limit;
    unsigned int value = frame_next_random_word();
    value &= 0x7fff;
    radius = (short)radius;
    return (short)((((radius * 2 + 1) * value) >> 15) - radius);
}
