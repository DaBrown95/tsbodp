#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "view_math.h"
#include "frame_actor_distance.h"
void frame_actor_state_9(struct FrameObject *object)
{
 unsigned int distance;
 struct FrameObject *actor=g_frame_actor_need_input.views[g_frame_actor_need_input.local_player].actor;
 if(((struct FrameActorObject *)object)->variant_state!=9&&((struct FrameActorObject *)object)->variant_state!=5) {
  distance=view_point_distance(object->position,actor->position)>>16;
  if(distance<((struct FrameActorFleeWork *)object)->enter_range) {
   frame_set_variant_state(object,9);
   ((struct FrameActorFleeWork *)object)->saved_speed=((struct FrameActorObject *)object)->speed;
   ((struct FrameActorObject *)object)->speed*=2;
   frame_set_actor_direction(object,frame_random_bounded(7));
   ((struct FrameActorFleeWork *)object)->countdown=frame_random_range(10,((struct FrameActorFleeWork *)object)->turn_delay);
  }
 }
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 3:
  if(--((struct FrameActorFleeWork *)object)->countdown==65535) {
   frame_set_variant_state(object,7);
   ((struct FrameActorFleeWork *)object)->countdown=frame_random_range(15,((struct FrameActorFleeWork *)object)->wait_delay);
  }
  break;
 case 5:
  if(object->flags&0x400000){transition_object_set_state(object,1);object->flags&=~0x10u;}
  break;
 case 7:
  if(--((struct FrameActorFleeWork *)object)->countdown==65535) {
   frame_set_variant_state(object,3);
   frame_set_actor_direction(object,frame_random_bounded(7));
   ((struct FrameActorFleeWork *)object)->countdown=frame_random_range(10,((struct FrameActorFleeWork *)object)->turn_delay);
  }
  break;
 case 9:
  {
   distance=view_point_distance(object->position,actor->position)>>16;
   if(distance>((struct FrameActorFleeWork *)object)->leave_range) {
    frame_set_variant_state(object,7);
    ((struct FrameActorFleeWork *)object)->countdown=frame_random_range(15,((struct FrameActorFleeWork *)object)->wait_delay);
    ((struct FrameActorObject *)object)->speed=((struct FrameActorFleeWork *)object)->saved_speed;
   } else if(--((struct FrameActorFleeWork *)object)->countdown==65535) {
    frame_set_actor_direction(object,frame_random_bounded(7));
    ((struct FrameActorFleeWork *)object)->countdown=frame_random_range(10,((struct FrameActorFleeWork *)object)->turn_delay);
   }
  }
  break;
 }
}
