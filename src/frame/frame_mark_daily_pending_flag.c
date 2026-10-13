#include "frame_daily_flag_creation.h"

void frame_mark_daily_pending_flag(unsigned int index)
{
    unsigned int *flags;
    if (index <= 31) {
        register unsigned int base asm("r2") = (unsigned int)&g_display_daily_world;
        flags = (unsigned int *)(base + 0x71c);
    } else {
        {
            register unsigned int base asm("r2") = (unsigned int)&g_display_daily_world;
            flags = (unsigned int *)(base + 0x720);
        }
        index -= 32;
    }
    *flags |= 1u << index;
}

asm(".align 2, 0");
