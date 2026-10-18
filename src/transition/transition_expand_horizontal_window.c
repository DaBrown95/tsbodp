#include "transition_horizontal_windows.h"
#include "irq.h"
extern void irq_wait_vblank(void);

/* A window expands horizontally from the centre. */
void transition_expand_horizontal(unsigned short targets)
{
    short left = 120, right;
    register volatile unsigned short *window asm("r4");
    register volatile unsigned short *window_register asm("r2")
        = (volatile unsigned short *)0x04000048;

    /* The cursor finishes before waiting; the window remains live across waits. */
    *window_register = 0;
    ++window_register;
    *window_register = 0x3F;
    window = (volatile unsigned short *)0x04000040;
    right = 120;
    *window = (left * 256) | right;
    window_register -= 3;
    *window_register = 160;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;

    do {
        irq_wait_vblank();
        left = (((int)left << 16) - 0x30000) >> 16;
        right = (((int)right << 16) + 0x30000) >> 16;
        *window = (left * 256) | right;
    } while (left >= 0);

    REG16(0x04000054) = 16;
    REG16(0x04000000) &= 0xDFFF;
}
