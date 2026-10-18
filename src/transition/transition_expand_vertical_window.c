#include "transition_vertical_windows.h"
#include "irq.h"
extern void irq_wait_vblank(void);

/* A window expands vertically from the centre. */
void transition_expand_vertical(unsigned short targets)
{
    short top = 80, bottom;
    register volatile unsigned short *window asm("r4");
    register volatile unsigned short *window_register asm("r2")
        = (volatile unsigned short *)0x04000048;

    /* The cursor finishes before waiting; the window remains live across waits. */
    *window_register = 0;
    ++window_register;
    *window_register = 0x3F;
    window_register -= 5;
    *window_register = 240;
    window = (volatile unsigned short *)0x04000044;
    bottom = 80;
    *window = (top * 256) | bottom;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;

    do {
        irq_wait_vblank();
        top = (((int)top << 16) - 0x20000) >> 16;
        bottom = (((int)bottom << 16) + 0x20000) >> 16;
        *window = (top * 256) | bottom;
    } while (top >= 0);

    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0xDFFF;
}
