#include "frame.h"

/* Incoming calls and the historical formal list remain unproved. */
void frame_set_motion_y(struct FrameObject *object,
    FrameU32 phase, short rate, short amplitude)
{
    object->phase_y = phase << 8;
    object->rate_y = rate;
    object->amplitude_y = amplitude;
}
