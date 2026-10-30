#include "frame_render.h"

/* Select the native low byte before capturing the actual sequence pointer. */
void frame_read_resource_frame_dimensions(
    struct FrameSpriteResource *resource, struct FramePoint *dimensions,
    unsigned int index)
{
    struct FrameSpriteSequence *sequence;
    struct FrameSpriteFrame *frame;

    index = (FrameU8)index;
    sequence = resource->sequence;
    frame = (struct FrameSpriteFrame *)
        ((FrameU8 *)sequence + 12 + sequence->frame_offsets[index]);

    dimensions->x = frame->width;
    dimensions->y = frame->height;
}
