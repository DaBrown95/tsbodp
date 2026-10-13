#include "frame_grid_selection.h"
void frame_step_local_need_effect_selection(void)
{
 struct FrameObject *actor;
 g_grid_selected_need_effect_object=0;
 {
  unsigned int address=g_input_config.local_player*12;
  address+=(unsigned int)&g_input_config;
  actor=*(struct FrameObject **)address;
 }
 display_time_step_world(&g_grid_selection_time_steps[g_actor_need_step_mode]);
 frame_set_actor_need_step_mode(0);
 frame_update_actor_routes();
 frame_refresh_scene_actor_schedule(g_frame_world_id,&g_display_world_clock);
 frame_update_need7_from_effects();
 frame_update_grid_need_effect_selection(actor);
 frame_grid_selection_interact(actor);
 frame_grid_selection_mark_attachments(actor);
}
