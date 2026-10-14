#include "irq.h"
#include "transition.h"

void transition_fade_black_out_refresh_twice(unsigned short targets) {
 unsigned short level;
 REG16(0x04000050) = targets | 0xc0;
 for (level = 0; level < 16; level += 1) {
  REG16(0x04000054) = level;
  transition_frame_update_08001168();
  display_step_palette_jobs();
  display_step_backgrounds();
  transition_stage_0802d054();
  irq_wait_vblank();
  transition_frame_update_08001168();
  display_step_palette_jobs();
  display_step_backgrounds();
  transition_stage_0802d054();
  irq_wait_vblank();
 }
}
