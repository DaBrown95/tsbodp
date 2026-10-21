#include "display.h"

void display_clear_forced_blank_vblank_unrooted_24bb8(void)
{
    volatile unsigned short *status = &DISPLAY_REG16(0x04000004);
    unsigned int mask = 1;
poll:
    if (!(*status & mask))
        goto poll;
    DISPLAY_REG16(0x04000000) &= 0xff7f;
}
