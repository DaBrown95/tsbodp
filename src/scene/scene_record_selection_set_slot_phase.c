#include "scene_record_selection_handoffs.h"

void scene_record_selection_set_slot_phase(unsigned char direction, unsigned int phase)
{
 int displacement = 256 * 65536;
 int index;
 if (direction) displacement = -256 * 65536;
 for (index = 0; index <= 0; index++) {
  struct FrameObject *object = g_condition_panel_objects[index];
  if (object) {
   object->on_step = frame_scene_object_tick;
   transition_object_set_state(object, 14);
   object->motion_storage.motion.timer = 15;
   frame_begin_position_move(object, object->position.x - displacement,
    object->position.y, 16);
   frame_step_position_move(object);
   frame_set_variant_state(object, 3);
  }
 }
 display_set_background_scroll_target(1,
  g_display_background_system.backgrounds[1].position_x + displacement,
  g_display_background_system.backgrounds[1].position_y, 14);
 g_condition_panel_objects[4]->flags &= ~1U;
 g_condition_panel_objects[5]->flags &= ~1U;
 g_scene_request.unknown_10 = 2;
 g_scene_request.unknown_14 = 15;
 SCENE_RECORD_SELECTION_STATE->unknown_0c[1] = direction;
 SCENE_RECORD_SELECTION_STATE->return_phase = phase;
 audio_play_animation_cue(1);
}
