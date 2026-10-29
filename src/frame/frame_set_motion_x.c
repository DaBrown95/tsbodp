#include "frame.h"

/* Incoming calls and the historical formal list remain unproved. */
void frame_set_motion_x(struct FrameObject *object,
    FrameU32 phase, short rate, short amplitude)
{
    object->phase_x = phase << 8;
    object->rate_x = rate;
    object->amplitude_x = amplitude;
}
