#include "frame_tick.h"
FrameU8 frame_read_sequence_attachment(struct FrameObject *, struct FrameSpriteSequence *, FrameU8, struct FramePoint *);
FrameU8 frame_part_attachment_position(struct FrameObject *base, FrameU8 part, FrameU8 attachment, struct FramePoint *point)
{
 struct FrameTickObject *object = (struct FrameTickObject *)base;
 struct FrameSpriteSequence *sequence;
 FrameU8 direction_limit;
 if (base->flags & 0x20000000) direction_limit = 8;
 else direction_limit = 4;
 sequence = object->parts[part].variants[(signed char)object->requested_animation][(signed char)object->variant].sequence;
 if (frame_read_sequence_attachment(base, sequence, attachment, point) == 1) {
  point->y = base->position.y + (point->y << 16);
  if (base->unknown_12[0] > direction_limit)
   point->x = base->position.x - (point->x << 16);
  else
   point->x = base->position.x + (point->x << 16);
  return 1;
 }
 return 0;
}
asm(".align 2, 0");
