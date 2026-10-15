#include "scene_contact_activity_one.h"
#define STATE ((struct SceneContactActivityOneState*)g_scene_contact_state)
struct FrameObject *scene_contact_activity_one_create_spawn(void) {
 struct FrameObject *base=frame_allocate_object(1);struct SceneContactActivityOneObject *object=(void*)base;
 frame_set_position(base,STATE->primary->position.x,STATE->primary->position.y);
 object->contact_mode=0;object->double_size=0;object->layer=1;object->palette=2;
 frame_enable_object_flags(base,25);base->on_step=scene_contact_activity_one_step_spawn;frame_set_animation_record(base,&g_scene_contact_activity_one_spawn_resources);base->before_step=resource_object_before_step;return base;
}
asm(".align 2,0");
