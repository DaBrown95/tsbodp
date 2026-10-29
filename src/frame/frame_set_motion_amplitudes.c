#include "frame.h"

/* Incoming calls and the historical formal list remain unproved. */
void frame_set_motion_amplitudes(struct FrameObject *object,
    short amplitude_x, short amplitude_y)
{
    object->amplitude_x = amplitude_x;
    object->amplitude_y = amplitude_y;
}
