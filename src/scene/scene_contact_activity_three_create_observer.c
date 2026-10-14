#include "scene_contact_activity_three.h"
struct FrameObject *scene_contact_activity_three_create_observer(void) {
 struct FrameObject *base=frame_allocate_scene_object();struct SceneContactActivityThreeObject *object=(void*)base;
 object->id=9;object->contact_mode=0;object->double_size=0;object->layer=0;object->palette=11;
 frame_set_position(base,120*65536,176*65536);
 frame_set_animation_record(base,&g_scene_contact_activity_three_observer_animation);
 return base;
}
asm(".align 2,0");
