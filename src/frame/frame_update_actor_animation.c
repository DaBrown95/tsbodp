#include "frame_actor_runtime.h"
void frame_update_actor_animation(struct FrameObject *base)
{
 struct FrameActorObject *object = (struct FrameActorObject *)base;
 if (object->pending_updates) {
  if (object->pending_updates & 0x10)
   frame_request_animation((struct FrameCommandObject *)object, (FrameU8)object->requested_animation);
  if (object->requested_animation == 6 || object->requested_animation == 4)
   frame_refresh_velocity(base);
  else frame_stop_motion(base);
 }
}
asm(".align 2, 0");
