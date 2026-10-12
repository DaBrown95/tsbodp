#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

void frame_set_actor_direction(struct FrameObject *object, unsigned char direction)
{
 if (((struct FrameActorObject *)object)->direction != direction) {
  ((struct FrameActorObject *)object)->direction = direction;
  ((struct FrameActorObject *)object)->pending_updates |= 0x10;
 }
}
asm(".align 2, 0");
