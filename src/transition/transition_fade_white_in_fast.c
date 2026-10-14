#include "irq.h"
#include "transition.h"

void transition_fade_white_in_fast(unsigned short targets) {
 int level;
 REG16(0x04000050) = targets | 0x80;
 for (level = 16; level >= 0; level += -2) {
  REG16(0x04000054) = level;
  transition_frame_update_08001168();
  display_step_backgrounds();
  display_step_palette_jobs();
  transition_stage_0802d054();
  irq_wait_vblank();
  irq_wait_vblank();
 }
}
