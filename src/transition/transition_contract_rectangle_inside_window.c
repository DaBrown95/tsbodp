#include "transition_rectangle_windows.h"
#include "irq.h"
extern void irq_wait_vblank(void);

/* A rectangle contracts towards the centre with the layers inside it. */
void transition_contract_rectangle_inside_window(unsigned short targets)
{
    short left = 0, right = 240, top = 0, bottom = 160;

    REG16(0x04000048) = 0x3F;
    REG16(0x0400004A) = top;
    REG16(0x04000040) = right;
    REG16(0x04000044) = bottom;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;

    do {
        irq_wait_vblank();
        top += 2;
        bottom -= 2;
        left += 3;
        right -= 3;
        REG16(0x04000040) = (left << 8) | right;
        REG16(0x04000044) = (top << 8) | bottom;
    } while (top <= 80);

    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0x9FFF;
}
