#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_step_secondary(struct FrameObject *base) {
 struct FrameActorObject *object=(void *)base;
 switch(object->variant_state) {
 case 0:{
  unsigned char changed=0;
  if(!(STATE->events&128) && STATE->amount==13) {
   frame_request_animation((struct FrameCommandObject *)object,3);STATE->events|=128;changed=1;
  } else if(!(STATE->events&64) && STATE->amount==7) {
   frame_request_animation((struct FrameCommandObject *)object,2);STATE->events|=64;changed=1;
  } else if(!(STATE->events&32) && STATE->amount==4) {
   frame_request_animation((struct FrameCommandObject *)object,1);STATE->events|=32;changed=1;
  } else {
   if(STATE->amount==0)STATE->events&=31;
  }
  if(changed)frame_set_variant_state((struct FrameObject *)object,1);
  break;
 }
 case 1:
  if(frame_object_has_flags((struct FrameObject *)object,0x400000)) {
   frame_request_animation((struct FrameCommandObject *)object,0);frame_set_variant_state((struct FrameObject *)object,0);
  }
  break;
 case 2:
  if(frame_object_has_flags((struct FrameObject *)object,0x400000)) {
   frame_set_variant_state((struct FrameObject *)object,3);frame_request_animation((struct FrameCommandObject *)object,0);frame_disable_object_flags((struct FrameObject *)object,16);
  }
  break;
 }
 if((object->pending_updates&0x16)&&(object->pending_updates&0x14))frame_set_animation_variant((struct FrameObject *)object,object->requested_animation,g_frame_actor_direction_variants_signed[object->direction]);
 object->pending_updates=0;
}
asm(".align 2,0");
