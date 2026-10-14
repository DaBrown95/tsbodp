#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
struct FrameObject *scene_contact_activity_six_create_second(unsigned int notice_parameter) {
 struct FrameObject *base=frame_allocate_scene_object();
 struct SceneContactActivitySixObject *object=(void *)base;
 object->id=3;object->subtype=frame_random_range(0,1);
 object->contact_mode=0;object->double_size=0;object->layer=3;object->palette=3;
 object->flags=9;
 frame_set_position(base,213*65536,161*65536);
 frame_set_animation_record(base,&g_scene_contact_activity_six_second_animations[object->subtype]);
 base->on_step=scene_contact_activity_six_step_second;
 base->velocity.y=g_scene_contact_activity_six_options[STATE->option].speed;
 ((struct SceneContactActivitySixNoticeObject *)base)->notice_parameter=notice_parameter;
 return base;
}
asm(".align 2,0");
