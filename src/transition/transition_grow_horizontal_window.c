#include "transition_single_windows.h"
#include "irq.h"

extern void irq_wait_vblank(void);

void transition_grow_horizontal_window(unsigned short targets) {
    short position = 0;
    register volatile unsigned short *window asm("r4");
    REG16(0x04000048) = 0;
    REG16(0x0400004A) = 0x3F;
    window = (volatile unsigned short *)0x04000040;
    *window = position;
    REG16(0x04000044) = 160;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;
    do {
        irq_wait_vblank();
        /* The high-halfword addition advances the 16-bit position by three. */
        position = (((int)position << 16) + 0x30000) >> 16;
        *window = position;
    } while (position <= 240);
    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0xDFFF;
}
