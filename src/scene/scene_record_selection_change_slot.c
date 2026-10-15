#include "scene_record_selection.h"
void scene_record_selection_change_slot(void)
{
 const unsigned char *pressed_bytes;
 unsigned int player;
 input_step_horizontal_pressed(&g_scene_request.parameter,0,3,1,
  g_frame_actor_need_input.local_player);
 pressed_bytes=(const unsigned char *)&g_input_local_pressed;
 player=g_frame_actor_need_input.local_player;
 scene_record_selection_set_slot_phase_original(
  (unsigned char)(pressed_bytes[player*2] & 16),3);
}
