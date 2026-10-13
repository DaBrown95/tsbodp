#include "frame_random.h"

unsigned int frame_next_random_word(void)
{
    register unsigned int result asm("r0");

    if (--g_frame_random_remaining >= 0) {
        register unsigned int value asm("r1") = *g_frame_random_next++;
        value ^= value >> 11;
        value ^= (value << 7) & 0x9d2c5680;
        value ^= (value << 15) & 0xefc60000;
        g_frame_random_last_byte = (result = value ^ (value >> 18));
    } else {
        result = frame_random_refill();
    }
    return result;
}
