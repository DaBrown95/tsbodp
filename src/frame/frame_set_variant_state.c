#include "frame_command.h"
void frame_set_variant_state(struct FrameObject *base, FrameU8 variant)
{
 struct FrameCommandObject *object = (struct FrameCommandObject *)base;
 if (object->variant_state != variant) {
  object->variant_state = variant;
  object->pending_updates |= 2;
 }
}
asm(".align 2, 0");
