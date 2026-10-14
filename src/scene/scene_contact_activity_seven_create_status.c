#include "scene_contact_activity_seven.h"
struct FrameObject *scene_contact_activity_seven_create_status(void) {
 struct FrameActorObject *object=(void *)frame_allocate_object(2);
 frame_set_position((struct FrameObject *)object,16*65536,128*65536);
 FLAGS(object)->contact_mode=0;FLAGS(object)->double_size=0;FLAGS(object)->layer=0;FLAGS(object)->palette=3;
 frame_enable_object_flags((struct FrameObject *)object,0x200001);
 frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_seven_status_animation);
 object->before_step=resource_object_before_step;
 return (struct FrameObject *)object;
}
