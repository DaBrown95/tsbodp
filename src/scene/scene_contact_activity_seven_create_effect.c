#include "scene_contact_activity_seven.h"
struct FrameObject *scene_contact_activity_seven_create_effect(unsigned char kind) {
 struct FrameActorObject *object=(void *)frame_allocate_object(1);
 frame_set_position((struct FrameObject *)object,111*65536,32*65536);
 FLAGS(object)->contact_mode=0;FLAGS(object)->double_size=0;FLAGS(object)->layer=1;FLAGS(object)->palette=2;
 frame_enable_object_flags((struct FrameObject *)object,25);
 object->on_step=scene_contact_activity_seven_step_effect;
 TIMER(object)=g_scene_contact_activity_seven_options[STATE->option].timer;
 if(kind)frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_seven_effect_first_animation);
 else frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_seven_effect_second_animation);
 object->before_step=resource_object_before_step;
 return (struct FrameObject *)object;
}
