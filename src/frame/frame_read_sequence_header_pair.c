#include "frame_tick.h"

void frame_read_sequence_header_pair(struct FrameObject *base,
                                                  struct FramePoint *point)
{
    struct FrameTickObject *object = (struct FrameTickObject *)base;
    struct FrameSpriteSequence *sequence = object->resource->sequence;
    point->x = sequence->unknown_00[0];
    point->y = sequence->unknown_00[1];
}
