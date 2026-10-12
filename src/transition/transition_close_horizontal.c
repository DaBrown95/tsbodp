#include "irq.h"
extern void irq_wait_vblank(void);

/* Window 0 moves right by three pixels after each VBlank. */
void transition_close_horizontal(unsigned short targets) {
 short x = 0;
 REG16(0x04000048) = 0;
 REG16(0x0400004A) = 0x3F;
 REG16(0x04000040) = 240;
 REG16(0x04000044) = 160;
 REG16(0x04000000) |= 0x2000;
 REG16(0x04000050) = targets | 0xC0;
 irq_wait_vblank();
 REG16(0x04000054) = 0;
 do {
  irq_wait_vblank();
  x = (((int)x << 16) + 0x30000) >> 16;
  REG16(0x04000040) = (x << 8) | 240;
 } while (x <= 240);
 REG16(0x04000000) &= 0xDFFF;
}
