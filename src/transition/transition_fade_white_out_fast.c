#include "irq.h"
#include "transition.h"

void transition_fade_white_out_fast(unsigned short targets) {
 int level;
 REG16(0x04000050) = targets | 0x80;
 for (level = 0; level <= 16; level += 2) {
  REG16(0x04000054) = level;
  transition_frame_update_08001168();
  display_step_backgrounds();
  transition_palette_update_080117d4();
  transition_stage_0802d054();
  irq_wait_vblank();
  irq_wait_vblank();
 }
}
