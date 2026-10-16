#include "frame_actor_24420.h"

void frame_make_direction_vector(struct FramePoint *out, unsigned int direction,
                                 int scale)
{
    out->x = frame_fixed_multiply(g_frame_direction_16[direction].x, scale);
    out->y = frame_fixed_multiply(g_frame_direction_16[direction].y, scale);
}
