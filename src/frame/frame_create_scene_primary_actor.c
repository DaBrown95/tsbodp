#include "frame_scene_player.h"
struct FrameObject *frame_create_scene_primary_actor(void) {
 struct FrameObject *object=frame_allocate_object(27);
 object->flags=0x00100018;
 object->unknown_4c[0]=0;
 frame_set_position(object,0,0);
 transition_object_set_state(object,0);
 frame_set_animation_record(object,&g_frame_scene_primary_animation);
 frame_acquire_palette_slot(object,6);
 object->on_step=frame_scene_primary_tick;
 object->display_layer=0;
 object->before_step=resource_object_before_step;
 return object;
}
asm(".align 2,0");
