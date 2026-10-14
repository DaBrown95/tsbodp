#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
struct FrameObject *scene_contact_activity_six_create_gauge(void) {
 unsigned int variant;
 struct SceneContactActivitySixObject *object=(void *)frame_allocate_scene_object();
 object->id=4;object->contact_mode=0;object->double_size=0;object->layer=0;object->palette=4;
 object->flags=9;frame_set_position((struct FrameObject *)object,0,0);
 variant=STATE->option;
 if(variant>2)variant=2;else if(variant)variant=1;
 object->subtype=variant;
 frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_six_gauge_animations[object->subtype]);
 ((struct FrameObject *)object)->on_step=scene_contact_activity_six_step_gauge;
 return (struct FrameObject *)object;
}
asm(".align 2,0");
