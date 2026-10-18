#include "transition_horizontal_windows.h"
#include "irq.h"
extern void irq_wait_vblank(void);

/* Two windows grow from opposite edges towards the centre. */
void transition_join_horizontal(unsigned short targets)
{
    short left = 0, right = 240;
    register volatile unsigned short *window asm("r4");

    REG16(0x04000048) = 0;
    REG16(0x0400004A) = 0x3F;
    {
        volatile unsigned short *window_register
            = (volatile unsigned short *)0x04000040;
        *window_register = left;
        window_register += 2;
        *window_register = 160;
    }

    /* This persistent window pointer remains live across each wait. */
    window = (volatile unsigned short *)0x04000042;
    *window = (right << 8) | 240;
    REG16(0x04000046) = 160;
    REG16(0x04000000) |= 0x6000;
    REG16(0x04000050) = targets | 0xC0;

    do {
        irq_wait_vblank();
        left += 3;
        right -= 3;
        REG16(0x04000040) = left;
        *window = (right << 8) | 240;
    } while (left <= 120);

    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0x9FFF;
}
