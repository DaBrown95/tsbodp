#include "scene_request_queue.h"
void scene_step_request_handoff(void)
{
 transition_link_update();
 ++g_frame_allocation_epoch;
 if(scene_request_changed()) {
  g_game_flags|=0x10;
  scene_run_end_callback();
  g_scene_queued_request.unknown_00&=~0x80u;
  g_game_flags&=~0x800u;
  g_scene_previous_request=g_scene_request;
  g_scene_request=g_scene_queued_request;
  scene_run_begin_callback();
  g_game_flags&=~0x10u;
 }
 ++g_irq_context->frame_work_count;
 input_poll();
 scene_run_step_callback();
 frame_request_refresh();
 display_step_backgrounds();
 scene_update_windows_080489c4();
 transition_palette_update_080117d4();
 frame_prepare_oam_transfer();
}
