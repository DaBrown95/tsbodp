#include "transition_vertical_windows.h"
#include "irq.h"
extern void irq_wait_vblank(void);

/* A window contracts vertically towards the centre. */
void transition_contract_vertical(unsigned short targets)
{
    short top = 0, bottom = 160;

    REG16(0x04000048) = 0;
    REG16(0x0400004A) = 0x3F;
    REG16(0x04000040) = 240;
    REG16(0x04000044) = bottom;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;
    irq_wait_vblank();
    REG16(0x04000054) = 0;

    do {
        irq_wait_vblank();
        top += 2;
        bottom -= 2;
        REG16(0x04000044) = (top << 8) | bottom;
    } while (top <= 79);

    REG16(0x04000000) &= 0xDFFF;
}
