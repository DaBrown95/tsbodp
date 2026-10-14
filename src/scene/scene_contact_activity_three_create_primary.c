#include "scene_contact_activity_three.h"
struct FrameObject *scene_contact_activity_three_create_primary(void) {
 struct FrameObject *base=frame_allocate_scene_object();
 struct SceneContactActivityThreeObject *object=(void*)base;
 object->id=7;object->contact_mode=0;object->double_size=0;object->layer=0;object->palette=13;object->flags=1;
 frame_set_position(base,120*65536,160*65536);
 frame_set_animation_record(base,&g_scene_contact_activity_three_primary_animation);
 frame_set_animation_program(base,(struct FrameSpriteResource*)&g_scene_contact_activity_three_primary_animation,g_scene_contact_activity_three_primary_commands,0);
 return base;
}
asm(".align 2,0");
