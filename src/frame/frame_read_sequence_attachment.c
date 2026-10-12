#include "frame_tick.h"
FrameU8 frame_read_sequence_attachment(struct FrameObject *base, struct FrameSpriteSequence *sequence, FrameU8 attachment, struct FramePoint *point)
{
 struct FrameTickObject *object = (struct FrameTickObject *)base;
 if (attachment >= sequence->attachment_count) {
  return 0;
 } else {
  signed char *record = (signed char *)sequence + 12 + sequence->frame_offsets[object->frame] + 10 + attachment * 2;
  point->x = record[0];
  point->y = record[1];
  return 1;
 }
}
asm(".align 2, 0");
