#include "scene_contact_activity_seven.h"
unsigned char scene_contact_activity_seven_advance(struct FrameObject *base,unsigned char threshold,unsigned int animation,unsigned int state) {
 struct FrameActorObject *object=(void *)base;
 struct FrameSpriteSequence *sequence=object->resource->sequence;
 unsigned char result=0;
 STATE->presses++;
 if(STATE->presses>=threshold) {
 STATE->presses=0;TIMER(object)=20;
 if(object->previous_frame==sequence->frame_count-1) {
 if(object->variant_state!=5)frame_request_animation((struct FrameCommandObject *)object,animation);
 frame_set_variant_state(base,state);frame_disable_object_flags(base,16);result=1;
 } else frame_set_animation_frame((struct FrameTickObject *)object,object->previous_frame+1);
 }
 return result;
}
