#include "scene_contact_activity_seven.h"
unsigned char scene_contact_activity_seven_finish_animation(struct FrameObject *object,unsigned int animation,unsigned int state) {
 unsigned char result=0;
 if(frame_object_has_flags(object,0x400000)) {
 frame_request_animation((struct FrameCommandObject *)object,animation);
 frame_set_variant_state(object,state);result=1;
 }
 return result;
}
asm(".align 2,0");
