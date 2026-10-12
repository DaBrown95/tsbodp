#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
void frame_actor_state_34(struct FrameObject *object)
{
 struct FramePoint destination;
 unsigned char started = 0, found;
 switch (((struct FrameActorObject *)object)->variant_state) {
 case 0:
  found = frame_find_scene_target(&destination.x, &destination.y);
  if (found == 1) {
   frame_request_animation((struct FrameCommandObject *)object, 6);
   started = frame_begin_actor_route(object, &destination, &((struct FrameActorStateWork *)object)->movement_status, 0, 0);
  }
  if (!found || !started)
   frame_set_variant_state(object, 40);
  else
   frame_set_variant_state(object, 3);
  break;
 case 3:
  switch (((struct FrameActorStateWork *)object)->movement_status) {
  case 2: break;
  case 1:
   transition_object_set_state(object, 1);
   frame_cancel_actor_route(object);
   break;
  case 3:
   frame_set_variant_state(object, 40);
   frame_cancel_actor_route(object);
   break;
  }
  break;
 case 40:
  transition_object_set_state(object, 43);
  frame_set_variant_state(object, 0);
  break;
 }
}
asm(".align 2, 0");
