#include "frame_random.h"

unsigned short frame_random_bounded(unsigned short limit)
{
    register unsigned int value asm("r0") = frame_next_random_word();
    value &= 0x7fff;
    return (unsigned short)((value * (limit + 1)) >> 15);
}
