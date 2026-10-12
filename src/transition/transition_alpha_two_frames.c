#include "irq.h"
#include "transition.h"

void transition_alpha_two_frames(unsigned short first_targets, unsigned short second_targets, unsigned char limit) {
 unsigned short level;
 REG16(0x04000050) = first_targets | 0x40 | second_targets;
 for (level = 0; level <= limit; level++) {
  REG16(0x04000052) = ((16 - level) << 8) | level;
  irq_wait_vblank();
  irq_wait_vblank();
 }
}
