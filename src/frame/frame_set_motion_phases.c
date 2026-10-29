#include "frame.h"

/* Incoming calls and the historical formal list remain unproved. */
void frame_set_motion_phases(struct FrameObject *object,
    FrameU32 phase_x, FrameU32 phase_y)
{
    object->phase_x = phase_x << 8;
    object->phase_y = phase_y << 8;
}
