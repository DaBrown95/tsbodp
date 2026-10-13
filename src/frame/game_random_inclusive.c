#include "frame_random.h"

unsigned int game_random_inclusive(unsigned short limit)
{
    register unsigned int value asm("r0") = frame_next_random_secondary_word();
    value &= 0x7fff;
    return (unsigned short)((value * (limit + 1)) >> 15);
}
