#include "irq.h"
extern void irq_wait_vblank(void);

static inline void set_rectangle_window_enabled(unsigned int enabled)
{
    if (enabled)
        REG16(0x04000000) |= 0x2000;
    else
        REG16(0x04000000) &= 0xDFFF;
}

/* Expand a window from its centre, keeping the initial packed endpoints. */
void transition_expand_rectangle_window(unsigned short targets)
{
    short left = 120;
    short right;
    short top = 80;
    short bottom;
    short initial_bottom;
    short initial_right;
    register unsigned short clear_value asm("r10");

    REG16(0x04000048) = 0x3F;
    REG16(0x0400004A) = clear_value = 0;
    initial_bottom = bottom = 80;
    initial_right = right = 120;
    REG16(0x04000040) = (left * 256) | initial_right;
    REG16(0x04000044) = (top * 256) | initial_bottom;
    set_rectangle_window_enabled(1);
    REG16(0x04000050) = targets | 0xC0;
    irq_wait_vblank();
    REG16(0x04000054) = clear_value;

    do {
        irq_wait_vblank();
        top -= 2;
        bottom += 2;
        left -= 3;
        right += 3;
        REG16(0x04000040) = (left * 256) | right;
        REG16(0x04000044) = (top * 256) | bottom;
    } while (top >= 0);

    set_rectangle_window_enabled(0);
}
