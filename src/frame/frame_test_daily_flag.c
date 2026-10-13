#include "frame_daily_flags.h"

unsigned int frame_test_daily_flag(unsigned int index)
{
    unsigned int *flags;
    if (index > 31) {
        {
            unsigned int base = (unsigned int)&g_display_daily_world;
            flags = (unsigned int *)(base + 0x718);
        }
        index -= 32;
    } else {
        unsigned int base = (unsigned int)&g_display_daily_world;
        flags = (unsigned int *)(base + 0x714);
    }
    return *flags & (1u << index);
}
asm(".align 2, 0");
