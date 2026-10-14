#include "scene_contact_activity_three.h"
struct FrameObject *scene_contact_activity_three_create_secondary(void) {
 struct FrameObject *base=frame_allocate_scene_object();
 struct SceneContactActivityThreeObject *object=(void*)base;
 object->id=8;object->contact_mode=0;object->double_size=0;object->layer=0;object->palette=12;object->flags=1;
 frame_set_position(base,234*65536,156*65536);
 frame_set_animation_record(base,&g_scene_contact_activity_three_secondary_animation);
 frame_set_animation_program(base,(struct FrameSpriteResource*)&g_scene_contact_activity_three_secondary_animation,g_scene_contact_activity_three_secondary_commands,0);
 return base;
}
asm(".align 2,0");
