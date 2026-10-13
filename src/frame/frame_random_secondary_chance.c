#include "frame_random.h"

unsigned char frame_random_secondary_chance(unsigned short limit)
{
    unsigned int value = frame_next_random_secondary_word();
    value &= 0x7fff;
    if (limit < ((value * 101) >> 15))
        return 0;
    else
        return 1;
}
