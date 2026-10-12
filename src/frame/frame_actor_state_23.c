#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

void frame_actor_state_23(struct FrameObject *object)
{
 switch (((struct FrameActorObject *)object)->variant_state) {
 case 0:
  frame_request_animation((struct FrameCommandObject *)object, 5);
  frame_set_variant_state(object, 19);
  break;
 case 19:
  if (object->flags & 0x400000) {
   frame_request_animation((struct FrameCommandObject *)object, 1);
   transition_object_set_state(object, ((struct FrameActorObject *)object)->default_state);
   frame_set_variant_state(object, 2);
  }
  break;
 }
}
asm(".align 2, 0");
