#include "scene_contact_activity_one.h"
struct FrameObject *scene_contact_activity_one_create_secondary(void) {
 struct FrameObject *base=frame_allocate_object(2);struct SceneContactActivityOneObject *object=(void*)base;
 frame_set_position(base,210*65536,20*65536);object->contact_mode=0;object->double_size=0;object->layer=0;object->palette=1;
 frame_enable_object_flags(base,0x200001);frame_set_animation_record(base,&g_scene_contact_activity_one_secondary_resources);base->before_step=resource_object_before_step;return base;
}
asm(".align 2,0");
