#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_carry.h"
void frame_actor_state_43(struct FrameObject *object)
{
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 0:
  frame_stop_motion(object);
  frame_set_actor_direction(object,4);
  frame_request_animation((struct FrameCommandObject *)object,1);
  frame_create_actor_effect(object,200,5,1);
  frame_set_variant_state(object,72);
  ((struct FrameActorCarryWork *)object)->timer=16;
  break;
 case 72:
  if(--((struct FrameActorCarryWork *)object)->timer==-1)transition_object_set_state(object,1);
  break;
 }
}
asm(".align 2, 0");
