#include "frame_command.h"
void frame_request_animation(struct FrameCommandObject *object, FrameU8 animation)
{
 if (!(object->id == 7 && object->subtype <= 31)) {
  if (animation == object->requested_animation) return;
  if ((object->id == 0 || object->id == 7) &&
      (FrameU8)(object->requested_animation - 2) <= 1 && animation == 1) return;
  object->requested_animation = animation;
  object->flags |= 0x10;
  object->pending_updates |= 4;
  object->flags &= ~0x400000;
 } else { frame_request_actor_animation(object, animation); }
}
asm(".align 2, 0");
