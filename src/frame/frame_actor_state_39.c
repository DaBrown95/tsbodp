#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_attachment.h"
void frame_actor_state_39(struct FrameObject *object)
{
 unsigned int status=((struct FrameActorStateWork *)object)->movement_status;
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 3:
  if(status==2)break;
  if(status==3) {frame_set_variant_state(object,19);frame_cancel_actor_route(object);}
  else if(status==1) {
   void *target;
   frame_cancel_actor_route(object);
   if(frame_find_action_target(object,((unsigned char*)object)[0x6a],&target)) {
    void *owner=((struct FrameActionTargetOwner *)target)->owner;
    if(((struct FrameActionOwnerCallbacks *)owner)->check(owner,object)) {
     if(((struct FrameActionOwnerCallbacks *)owner)->use(owner,object,((unsigned char*)object)[0x6a])==1) {
      frame_attach_actor(object,owner);
      frame_set_variant_state(object,41);
      break;
     }
    }
   }
   frame_set_variant_state(object,19);
  }
  break;
 case 19:
  frame_request_animation((struct FrameCommandObject *)object,1);
  transition_object_set_state(object,((struct FrameActorObject *)object)->default_state);
  frame_set_variant_state(object,2);
  break;
 }
}
