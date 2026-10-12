#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_direct_move.h"
void resource_activate_groups(unsigned char,unsigned char);
void frame_actor_state_13(struct FrameObject *object)
{
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 0:
  frame_set_variant_state(object,3);
  frame_request_animation((struct FrameCommandObject *)object,6);
  frame_set_actor_destination(object,&((struct FrameActorDirectMoveWork *)object)->point);
  break;
 case 3:
  if(frame_actor_face_destination(object)==1) {
   transition_object_set_state(object,((struct FrameActorObject *)object)->default_state);
   frame_set_variant_state(object,2);
   frame_set_actor_direction(object,((struct FrameActorDirectMoveWork *)object)->saved_direction);
   if(object->id==0){frame_stop_motion(object);frame_request_animation((struct FrameCommandObject *)object,1);}
   object->flags=((struct FrameActorDirectMoveWork *)object)->saved_flags;
   resource_activate_groups(((struct FrameActorDirectMoveWork *)object)->group,((struct FrameActorDirectMoveWork *)object)->index);
  } else if(object->id==0)frame_refresh_velocity(object);
  break;
 default:frame_actor_step_wait_phase(object);break;
 }
}
asm(".align 2, 0");
