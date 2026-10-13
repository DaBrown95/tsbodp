#include "frame_random.h"

unsigned int frame_random_refill(void)
{
    unsigned int *storage;
    unsigned int *out = (unsigned int *)g_frame_random_buffer_address;
    unsigned int *ahead = out + 2;
    unsigned int *tap = out + 397;
    unsigned int previous, current;
    unsigned int *first;
    int available, threshold;

    /* Retain the storage address across the optional seed pass. */
    if ((available = g_frame_random_remaining, threshold = -1,
         storage = &g_frame_random_buffer_address, available < threshold)) {
        unsigned int seed = g_frame_random_seed | 1;
        unsigned int *next = out;
        g_frame_random_remaining = 0;
        *next++ = seed;
        {
            int remaining;
            for (remaining = 623; remaining; --remaining) {
                seed *= 69069;
                *next++ = seed;
            }
        }
    }
    g_frame_random_remaining = 623;
    first = (unsigned int *)*storage;
    g_frame_random_next = first + 1;
    previous = first[0];
    current = first[1];
    {
        int remaining;
        for (remaining = 227; remaining; --remaining) {
            *out++ = *tap++ ^
                (((previous & 0x80000000) | (current & 0x7fffffff)) >> 1) ^
                ((current & 1) ? 0x9908b0df : 0);
            previous = current;
            current = *ahead++;
        }
    }
    tap = (unsigned int *)*storage;
    {
        int remaining;
        for (remaining = 396; remaining; --remaining) {
            *out++ = *tap++ ^
                (((previous & 0x80000000) | (current & 0x7fffffff)) >> 1) ^
                ((current & 1) ? 0x9908b0df : 0);
            previous = current;
            current = *ahead++;
        }
    }
    current = ((unsigned int *)*storage)[0];
    {
        unsigned int high = previous & 0x80000000;
        unsigned int mixed = current & 0x7fffffff;
        mixed = (mixed | high) >> 1;
        *out = *tap ^ mixed;
        if (current & 1) *out ^= 0x9908b0df;
    }
    current ^= current >> 11;
    current ^= (current << 7) & 0x9d2c5680;
    current ^= (current << 15) & 0xefc60000;
    current ^= current >> 18;
    return current;
}
