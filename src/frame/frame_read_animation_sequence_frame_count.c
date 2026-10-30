#include "frame_tick.h"

FrameU32 frame_read_animation_sequence_frame_count(
    struct FrameAnimationCore *animation)
{
    return animation->resource->sequence->frame_count;
}
