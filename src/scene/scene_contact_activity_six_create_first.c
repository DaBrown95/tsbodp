#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
struct FrameObject *scene_contact_activity_six_create_first(void) {
 struct FrameObject *base=frame_allocate_scene_object();
 struct SceneContactActivitySixObject *object=(void *)base;
 object->id=2;object->subtype=frame_random_range(0,3);
 object->contact_mode=0;object->double_size=0;object->layer=3;object->palette=2;
 object->flags=9;
 frame_set_position(base,187*65536,160*65536);
 frame_set_animation_record(base,&g_scene_contact_activity_six_first_animations[object->subtype]);
 base->on_step=scene_contact_activity_six_step_first;
 base->velocity.y=g_scene_contact_activity_six_options[STATE->option].speed;
 return base;
}
asm(".align 2,0");
