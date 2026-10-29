#include "frame.h"

/* Incoming calls and the historical formal list remain unproved. */
void frame_set_motion_rates(struct FrameObject *object,
    short rate_x, short rate_y)
{
    object->rate_x = rate_x;
    object->rate_y = rate_y;
}
