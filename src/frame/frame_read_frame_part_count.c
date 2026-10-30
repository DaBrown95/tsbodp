#include "frame_render.h"

FrameU32 frame_read_frame_part_count(
    const struct FrameSpriteFrame *frame)
{
    return frame->count_flags & 0x1f;
}
