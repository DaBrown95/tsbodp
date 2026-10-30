#include "frame_render.h"

void frame_read_resource_sequence_header_pair(
    struct FrameSpriteResource *resource, struct FramePoint *point)
{
    struct FrameSpriteSequence *sequence = resource->sequence;
    point->x = sequence->unknown_00[0];
    point->y = sequence->unknown_00[1];
}
