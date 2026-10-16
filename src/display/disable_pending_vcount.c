#include "display_pending_scroll.h"

void display_disable_pending_vcount(void)
{
    *(volatile unsigned short *)0x04000200 &= 0xfffb;
    *(volatile unsigned short *)0x04000202 |= 4;
    *(volatile unsigned short *)0x04000004 &= 0xdf;
}
