#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

void frame_actor_state_26(struct FrameObject *object)
{
struct FramePoint tile, point;
 void *target;
 unsigned int action;
 FrameU8 used;
 switch (((struct FrameActorObject *)object)->variant_state) {
 case 0:
  if (resource_group_point_count(((struct FrameActorStateWork *)object)->waypoint_group)) {
   ((struct FrameActorStateWork *)object)->waypoint_index = frame_random_range(0, resource_group_point_count(((struct FrameActorStateWork *)object)->waypoint_group)-1);
   tile = resource_read_group_point( ((struct FrameActorStateWork *)object)->waypoint_group, ((struct FrameActorStateWork *)object)->waypoint_index);
   point=tile;
   point.x <<= 16;
   point.y <<= 16;
   if (frame_begin_actor_route(object, &point, &((struct FrameActorStateWork *)object)->movement_status, 0, 0) == 1) {
    frame_request_animation((struct FrameCommandObject *)object, 6);
    frame_set_variant_state(object, 3);
   } else {
    frame_request_animation((struct FrameCommandObject *)object, 1);
   }
   break;
  }
  goto wait;
 case 3:
  if (((struct FrameActorStateWork *)object)->movement_status != 3 &&
      ((struct FrameActorStateWork *)object)->movement_status != 1 &&
      ((struct FrameActorStateWork *)object)->movement_status != 0)
   break;
  frame_cancel_actor_route(object);
wait:
  frame_request_animation((struct FrameCommandObject *)object, 1);
  ((struct FrameActorStateWork *)object)->timer = ((struct FrameActorStateWork *)object)->wait_units * 30;
  frame_set_variant_state(object, 7);
  break;
 case 7:
  if (--((struct FrameActorStateWork *)object)->timer == -1) {
   frame_cancel_actor_route(object);
   frame_set_variant_state(object, 61);
  }
  break;
 case 2:
  frame_cancel_actor_route(object);
  frame_set_variant_state(object, 0);
  break;
 case 61:
  if (frame_find_need_target(object, &target, &action) == 1)
   used = frame_actor_use_target(target, object, (FrameU8)action);
  else
   used = 0;
  if (!used)
   frame_set_variant_state(object, 0);
  break;
 }
}
asm(".align 2, 0");
