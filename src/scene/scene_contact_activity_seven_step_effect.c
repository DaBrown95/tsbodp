#include "scene_contact_activity_seven.h"
void scene_contact_activity_seven_step_effect(struct FrameObject *object) {
 if(--TIMER(object)==-1)frame_enable_object_flags(object,2);
}
asm(".align 2,0");
