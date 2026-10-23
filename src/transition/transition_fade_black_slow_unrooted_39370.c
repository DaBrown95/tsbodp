#include "display.h"
#include "transition.h"

void transition_fade_black_slow_unrooted_39370(unsigned int unused,
                                             unsigned short targets)
{
    unsigned short level;

    DISPLAY_REG16(0x04000050) = targets | 0xc0;
    for (level = 0; level < 128; level++) {
        register unsigned int quotient asm("r0") =
            (unsigned short)display_bios_div(level, 8);
        register volatile unsigned short *brightness asm("r1") =
            (volatile unsigned short *)0x04000054;
        *brightness = quotient;
        irq_wait_vblank();
    }
}
