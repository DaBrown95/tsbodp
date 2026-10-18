#include "transition_single_windows.h"
#include "irq.h"

extern void irq_wait_vblank(void);

/* Keep the right edge at 240 while the left edge decreases through zero. */
void transition_grow_horizontal_window_from_right(unsigned short targets)
{
    short left = 240;
    register volatile unsigned short *window_register asm("r2");
    register volatile unsigned short *window asm("r4");

    window_register = (volatile unsigned short *)0x04000048;
    *window_register = 0;
    ++window_register;
    *window_register = 0x3F;
    window = (volatile unsigned short *)0x04000040;
    *window = (left * 256) | 240;
    REG16(0x04000044) = 160;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;

    do {
        irq_wait_vblank();
        left -= 3;
        *window = (left * 256) | 240;
    } while (left >= 0);

    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0xDFFF;
}
