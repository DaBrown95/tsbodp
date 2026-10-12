#include "irq.h"
#include "transition.h"
#include "transition_alpha.h"

void transition_alpha_reverse(unsigned short first_targets, unsigned short second_targets, int limit, int frames) {
 int level, remaining;
 unsigned short a, b;
 REG16(0x04000050) = first_targets | 0x40 | (second_targets << 8);
 for (level = limit; level >= 0; level--) {
  a = level;
  b = 16 - level;
  g_transition_alpha_a.value = a << 8;
  g_transition_alpha_b.value = b << 8;
  REG16(0x04000052) = a | (b << 8);
  for (remaining = frames; remaining > 0; remaining--) irq_wait_vblank();
 }
}
