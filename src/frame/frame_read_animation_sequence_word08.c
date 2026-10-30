#include "frame_tick.h"

FrameU32 frame_read_animation_sequence_word08(
    struct FrameAnimationCore *animation)
{
    return animation->resource->sequence->unknown_08;
}
