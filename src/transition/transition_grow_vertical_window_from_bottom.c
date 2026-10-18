#include "transition_single_windows.h"
#include "irq.h"

extern void irq_wait_vblank(void);

/* Keep the bottom edge at 160 while the top edge decreases through zero. */
void transition_grow_vertical_window_from_bottom(unsigned short targets)
{
    short top = 160;
    register volatile unsigned short *window_register asm("r2");
    register volatile unsigned short *window asm("r4");

    window_register = (volatile unsigned short *)0x04000048;
    *window_register = 0;
    ++window_register;
    *window_register = 0x3F;
    window_register -= 5;
    *window_register = 240;
    window = (volatile unsigned short *)0x04000044;
    *window = (top * 256) | 160;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;

    do {
        irq_wait_vblank();
        top -= 2;
        *window = (top * 256) | 160;
    } while (top >= 0);

    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0xDFFF;
}
