#include "transition_rectangle_windows.h"
#include "irq.h"
extern void irq_wait_vblank(void);

/* A rectangle expands with the selected layers outside its bounds. */
void transition_expand_rectangle_outside_window(unsigned short targets)
{
    short left = 120, top = 80, right, bottom;

    {
        register volatile unsigned short *window_register asm("r2")
            = (volatile unsigned short *)0x04000048;
        *window_register = 0;
        ++window_register;
        *window_register = 0x3F;
    }
    REG16(0x04000040) = (left * 256) | (right = 120);
    REG16(0x04000044) = (top * 256) | (bottom = 80);
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;

    do {
        irq_wait_vblank();
        top -= 2;
        bottom += 2;
        left -= 3;
        right += 3;
        REG16(0x04000040) = (left * 256) | right;
        REG16(0x04000044) = (top * 256) | bottom;
    } while (top >= 0);

    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0x9FFF;
}
