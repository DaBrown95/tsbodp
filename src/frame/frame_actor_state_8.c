#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "view_math.h"
#include "frame_actor_distance.h"
void frame_actor_state_8(struct FrameObject *object)
{
 struct FrameObject *target=((struct FrameActorFollowWork *)object)->target;
 if(!target) {
  if(((struct FrameActorObject *)object)->variant_state!=7)frame_set_variant_state(object,7);
  return;
 }
 {
  struct FramePoint position;
  int distance;
  position=target->position;
  distance=view_point_distance(object->position,position)>>16;
  if(distance>220 && !(object->flags&0x1000)) {
   position.y+=85<<16;
   if(frame_point_near_any_view(position)) {
    object->position=position;
    return;
   }
  }
  switch(((struct FrameActorObject *)object)->variant_state) {
  case 3:
   if(((struct FrameActorFollowWork *)object)->range>distance) {
    frame_set_variant_state(object,7);
    ((struct FrameActorFollowWork *)object)->timer=((struct FrameActorFollowWork *)object)->wait_units;
   } else frame_actor_follow_target(object,target);
   break;
  case 7:
   if(((struct FrameActorFollowWork *)object)->timer==0) {
    if(((struct FrameActorFollowWork *)object)->range<distance)frame_set_variant_state(object,3);
   } else ((struct FrameActorFollowWork *)object)->timer--;
   break;
  case 13:
   if(--((struct FrameActorFollowWork *)object)->timer==-1) {frame_set_variant_state(object,7);((struct FrameActorFollowWork *)object)->timer=5;}
   break;
  default:
   if(((struct FrameActorObject *)object)->variant_state!=5) {
    ((struct FrameActorFollowWork *)object)->timer=((struct FrameActorFollowWork *)object)->wait_units;
    frame_set_variant_state(object,7);
   }
   break;
  }
 }
}
asm(".align 2, 0");
