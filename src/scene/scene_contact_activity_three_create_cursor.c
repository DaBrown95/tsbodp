#include "scene_contact_activity_three.h"
struct FrameObject *scene_contact_activity_three_create_cursor(void) {
 struct FrameObject *base=frame_allocate_scene_object();struct SceneContactActivityThreeObject *object=(void*)base;
 object->id=10;object->contact_mode=0;object->double_size=0;object->layer=0;object->palette=10;
 object->flags=1;
 frame_set_position(base,8*65536,112*65536);
 frame_set_animation_record(base,&g_scene_contact_activity_three_cursor_animation);
 return base;
}
asm(".align 2,0");
