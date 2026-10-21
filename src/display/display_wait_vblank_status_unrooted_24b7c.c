#include "display.h"

void display_wait_vblank_status_unrooted_24b7c(void)
{
    volatile unsigned short *status = &DISPLAY_REG16(0x04000004);
    unsigned int mask = 1;
poll:
    if (!(*status & mask))
        goto poll;
}
