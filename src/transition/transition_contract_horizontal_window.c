#include "transition_horizontal_windows.h"
#include "irq.h"
extern void irq_wait_vblank(void);

/* A window contracts horizontally towards the centre. */
void transition_contract_horizontal(unsigned short targets)
{
    short left = 0, right = 240;

    REG16(0x04000048) = 0;
    REG16(0x0400004A) = 0x3F;
    REG16(0x04000040) = right;
    REG16(0x04000044) = 160;
    REG16(0x04000000) |= 0x2000;
    REG16(0x04000050) = targets | 0xC0;
    irq_wait_vblank();
    REG16(0x04000054) = 0;

    do {
        irq_wait_vblank();
        left += 3;
        right -= 3;
        REG16(0x04000040) = (left << 8) | right;
    } while (left <= 119);

    REG16(0x04000000) &= 0xDFFF;
}
