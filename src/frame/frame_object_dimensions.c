#include "frame_tick.h"
void frame_object_dimensions(struct FrameObject *base, struct FramePoint *dimensions)
{
 struct FrameTickObject *object = (struct FrameTickObject *)base;
 struct FrameSpriteSequence *sequence = object->resource->sequence;
 struct FrameSpriteFrame *frame = (struct FrameSpriteFrame *)((FrameU8 *)sequence + 12 + sequence->frame_offsets[object->frame]);
 dimensions->x = frame->width;
 dimensions->y = frame->height;
}
