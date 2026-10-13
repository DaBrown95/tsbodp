#include "frame_random.h"

unsigned char frame_random_chance(unsigned short limit)
{
    unsigned int value = frame_next_random_word();
    value &= 0x7fff;
    if (limit < ((value * 101) >> 15))
        return 0;
    else
        return 1;
}
