#include "scene_record_selection_handoffs.h"

void scene_record_selection_set_phase(unsigned char direction, unsigned int phase)
{
 int displacement = 256 * 65536;
 int index;
 const struct FrameActorPaletteScenePoint *point;
 if (direction) displacement = -256 * 65536;
 index = 0;
 point = g_frame_actor_palette_scene_positions;
 for (; index <= 0; index++) {
  struct FrameObject *object = g_condition_panel_objects[index];
  if (object) {
   int x, y, start_x;
   object->on_step = frame_scene_object_tick;
   transition_object_set_state(object, 14);
   object->motion_storage.motion.timer = 15;
   x = point->x * 65536;
   start_x = x - displacement;
   y = point->y * 65536;
   frame_set_position(object, start_x, y);
   frame_begin_position_move(object, x, y, (unsigned short)(object->motion_storage.motion.timer + 1));
   frame_step_position_move(object);
   frame_set_variant_state(object, 3);
  }
 }
 display_set_background_position_x(1, displacement);
 display_set_background_scroll_target(1, 0,
  g_display_background_system.backgrounds[1].position_y, 14);
 g_scene_request.unknown_10 = 0;
 g_scene_request.unknown_14 = 15;
 SCENE_RECORD_SELECTION_STATE->unknown_0c[1] = direction;
 SCENE_RECORD_SELECTION_STATE->return_phase = phase;
}
