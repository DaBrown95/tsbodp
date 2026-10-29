#include "frame.h"

/* Incoming calls and the historical formal list remain unproved. */
void frame_reset_motion_y(struct FrameObject *object)
{
    object->phase_y = 0;
    object->rate_y = 0;
    object->amplitude_y = 0;
}
