#include "irq.h"
extern void irq_wait_vblank(void);

/* Two windows retreat from the centre in three-pixel steps. */
void transition_split_vertical(unsigned short targets) {
 short left = 80, right = 80;
 REG16(0x04000048) = 0;
 REG16(0x0400004A) = 0x3F;
 REG16(0x04000040) = 240;
 REG16(0x04000044) = left;
 REG16(0x04000042) = 240;
 REG16(0x04000046) = (left << 8) | 160;
 REG16(0x04000000) |= 0x6000;
 REG16(0x04000050) = targets | 0xC0;
 irq_wait_vblank();
 REG16(0x04000054) = 0;
 do {
  irq_wait_vblank();
  left = (((int)left << 16) - 0x20000) >> 16;
  right = (((int)right << 16) + 0x20000) >> 16;
  REG16(0x04000044) = left;
  REG16(0x04000046) = (right << 8) | 160;
 } while (left >= 0);
 REG16(0x04000000) &= 0x9FFF;
}
