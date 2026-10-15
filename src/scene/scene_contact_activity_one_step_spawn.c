#include "scene_contact_activity_one.h"
void scene_contact_activity_one_step_spawn(struct FrameObject *object) {
 if(frame_object_has_flags(object,0x400000))frame_enable_object_flags(object,2);
}
asm(".align 2,0");
