#include "frame_random.h"

int frame_random_secondary_range(int first, int last)
{
    int value = frame_next_random_secondary_word() & 0x7fff;

    last -= first;
    ++last;
    first += (value * last) >> 15;
    return first;
}
