#include "display_pending_scroll.h"

void display_pending_step_bg2_x(unsigned int *value, unsigned int *delta)
{
    unsigned int previous = *value >> 16;
    *value += *delta;
    while (!(*(volatile unsigned short *)0x04000004 & 2)) {
    }
    *(volatile unsigned short *)0x04000018 = previous;
}
