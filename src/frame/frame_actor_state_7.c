#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

void frame_actor_state_7(struct FrameObject *object)
{
 int index;
struct FramePoint tile, point;
 switch (((struct FrameActorObject *)object)->variant_state) {
 case 0:
  do {
   index = frame_random_range(0, resource_group_point_count(((struct FrameActorStateWork *)object)->waypoint_group) - 1);
  } while (index == ((struct FrameActorStateWork *)object)->waypoint_index);
  ((struct FrameActorStateWork *)object)->waypoint_index = index;
  tile = resource_read_group_point( ((struct FrameActorStateWork *)object)->waypoint_group, ((struct FrameActorStateWork *)object)->waypoint_index);
  point = tile;
  point.x <<= 16;
  point.y <<= 16;
  if (frame_begin_actor_route(object, &point, &((struct FrameActorStateWork *)object)->movement_status, 3, 0) == 1) {
   frame_set_variant_state(object, 3);
   frame_request_animation((struct FrameCommandObject *)object, 6);
  } else {
   frame_request_animation((struct FrameCommandObject *)object, 1);
  }
  break;
 case 3:
  if (((struct FrameActorStateWork *)object)->movement_status != 2) {
   if (((struct FrameActorStateWork *)object)->movement_status == 3)
    frame_cancel_actor_route(object);
   frame_request_animation((struct FrameCommandObject *)object, 1);
   ((struct FrameActorStateWork *)object)->timer = ((struct FrameActorStateWork *)object)->wait_units * 30;
   frame_set_variant_state(object, 7);
  }
  break;
 case 7:
  if (--((struct FrameActorStateWork *)object)->timer == -1) {
   frame_cancel_actor_route(object);
   frame_set_variant_state(object, 0);
  }
  break;
 }
}
asm(".align 2, 0");
