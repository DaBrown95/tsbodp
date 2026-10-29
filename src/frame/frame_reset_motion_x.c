#include "frame.h"

/* Incoming calls and the historical formal list remain unproved. */
void frame_reset_motion_x(struct FrameObject *object)
{
    object->phase_x = 0;
    object->rate_x = 0;
    object->amplitude_x = 0;
}
