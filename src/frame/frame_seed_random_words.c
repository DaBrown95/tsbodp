#include "frame_random.h"

void frame_seed_random_words(unsigned int seed)
{
    unsigned int value = seed | 1;
    unsigned int *next = (unsigned int *)g_frame_random_buffer_address;
    int remaining;

    g_frame_random_remaining = 0;
    *next++ = value;
    for (remaining = 623; remaining; --remaining) {
        value *= 69069;
        *next++ = value;
    }
}
