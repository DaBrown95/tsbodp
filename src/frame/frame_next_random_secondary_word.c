#include "frame_random.h"

unsigned int frame_next_random_secondary_word(void)
{
    unsigned int value;

    if (--g_frame_random_secondary_remaining < 0) {
        g_frame_random_secondary_remaining = 623;
        g_frame_random_secondary_next =
            (unsigned int *)(g_frame_random_buffer_address + 4);
    }
    value = *g_frame_random_secondary_next++;
    value ^= value >> 11;
    value ^= (value << 7) & 0x9d2c5680;
    value ^= (value << 15) & 0xefc60000;
    return value ^ (value >> 18);
}
