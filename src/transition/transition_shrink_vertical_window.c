#include "transition_single_windows.h"
#include "irq.h"

extern void irq_wait_vblank(void);

void transition_shrink_vertical_window(unsigned short targets) {
    short position = 160;
    unsigned short zero;
    /* The real window pointer remains live across the waits. */
    register volatile unsigned short *window asm("r4");
    /* Share zero with the initial brightness store. */
    REG16(0x04000048) = (zero = 0);
    REG16(0x0400004A) = 0x3F;
    REG16(0x04000040) = 240;
    window = (volatile unsigned short *)0x04000044;
    *window = position;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;
    irq_wait_vblank();
    REG16(0x04000054) = zero;
    do {
        irq_wait_vblank();
        position = (((int)position << 16) - 0x20000) >> 16;
        *window = position;
    } while (position >= 0);
    REG16(0x04000000) &= 0xDFFF;
}
