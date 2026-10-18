#include "transition_vertical_windows.h"
#include "irq.h"
extern void irq_wait_vblank(void);

/* Two windows grow vertically from opposite edges towards the centre. */
void transition_join_vertical(unsigned short targets)
{
    short top = 0, bottom = 160;
    register volatile unsigned short *window asm("r4");

    REG16(0x04000048) = 0;
    REG16(0x0400004A) = 0x3F;
    {
        volatile unsigned short *window_register
            = (volatile unsigned short *)0x04000040;
        *window_register = 240;
        window_register += 2;
        *window_register = top;
        --window_register;
        *window_register = 240;
    }

    /* This persistent window pointer remains live across each wait. */
    window = (volatile unsigned short *)0x04000046;
    *window = (bottom << 8) | 160;
    REG16(0x04000000) |= 0x6000;
    REG16(0x04000050) = targets | 0xC0;

    do {
        irq_wait_vblank();
        top += 2;
        bottom -= 2;
        REG16(0x04000044) = top;
        *window = (bottom << 8) | 160;
    } while (top <= 80);

    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0x9FFF;
}
