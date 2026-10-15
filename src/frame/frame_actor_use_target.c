#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_choices.h"
unsigned char frame_actor_use_target(void *target_base,struct FrameObject *actor,unsigned char action)
{
 struct FrameObject *target=target_base;
 void *owner=((struct FrameActionTargetOwner *)target)->owner;
 unsigned char result=0;
 if((unsigned char)((struct FrameActionOwnerCallbacks *)owner)->check(owner,actor)==1)result=frame_actor_route_to_target(actor,target,action);
 return result;
}
