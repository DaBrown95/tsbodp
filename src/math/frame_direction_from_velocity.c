#include "frame.h"
#include "view_math.h"

unsigned char frame_direction_from_velocity(struct FramePoint delta)
{
    unsigned char index = 0;
    if (delta.x < 0) {
        delta.x = -delta.x;
        index = 1;
    }
    if (delta.y < 0) {
        delta.y = -delta.y;
        index |= 2;
    }
    if (delta.x > delta.y * 3)
        index |= 4;
    if (delta.x * 3 < delta.y)
        index |= 8;
    return g_frame_direction_lookup[index];
}
