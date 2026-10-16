#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_finish.h"
void frame_actor_state_47(struct FrameObject *object)
{
 struct FrameObject *actor;
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 0 ... 45:break;
 case 46:case 47:case 48:case 51:case 73:
  frame_stop_motion(object);
  if(object->flags&0x400000) {
   frame_set_variant_state(object,6);
   frame_clear_animation_pending(object);
   actor=frame_create_actor(1,4,object->position.x+(15<<16),object->position.y-(25<<16));
   actor->spatial.bounds.upper=object->spatial.bounds.upper;
   actor->spatial.bounds.upper.y-=10;
   actor->spatial.bounds.lower=object->spatial.bounds.lower;
   actor->spatial.bounds.lower.y-=10;
   actor->before_step=0;
   frame_request_animation((struct FrameCommandObject *)actor,89);
   transition_object_set_state(actor,25);
   frame_set_variant_state(actor,0);
  }
  break;
 case 69:
  object->velocity.x=0;object->velocity.y=0;
  if(object->flags&0x400000) {
   frame_set_variant_state(object,6);
   actor=frame_create_actor(1,4,object->position.x+(15<<16),object->position.y-(25<<16));
   frame_request_animation((struct FrameCommandObject *)actor,89);
   transition_object_set_state(actor,25);
   frame_set_variant_state(actor,0);
  }
  break;
 }
}
