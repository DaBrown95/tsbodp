#include "frame_constructor.h"

void frame_set_directional_acceleration(struct FrameObject *object,
                                      unsigned int direction, int acceleration)
{
    object->acceleration.x = frame_fixed_multiply(
        g_frame_direction_16[direction].x, acceleration);
    object->acceleration.y = frame_fixed_multiply(
        g_frame_direction_16[direction].y, acceleration);
}
