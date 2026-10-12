#include "irq.h"
extern void irq_wait_vblank(void);

/* Window 0 moves downward by two pixels after each VBlank. */
void transition_close_vertical(unsigned short targets) {
 short y = 0;
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
  y = (((int)y << 16) + 0x20000) >> 16;
  REG16(0x04000044) = (y << 8) | 160;
 } while (y <= 160);
 REG16(0x04000000) &= 0xDFFF;
}
