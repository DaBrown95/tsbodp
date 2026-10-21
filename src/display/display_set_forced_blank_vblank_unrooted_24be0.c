#include "display.h"

void display_set_forced_blank_vblank_unrooted_24be0(void)
{
    volatile unsigned short *status = &DISPLAY_REG16(0x04000004);
    unsigned int mask = 1;
poll:
    if (!(*status & mask))
        goto poll;
    DISPLAY_REG16(0x04000000) |= 0x80;
}
