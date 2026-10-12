#include "frame.h"
#include "view_math.h"

void frame_make_velocity(struct FramePoint *output, unsigned int flags,
                         unsigned int direction, int speed)
{
    register const int *vectors asm("r4");
    if (flags & 0x20000000)
        vectors = g_frame_velocity_extended;
    else if (flags & 0x4000)
        vectors = g_frame_velocity_restricted;
    else
        vectors = g_frame_velocity_default;
    output->x = frame_fixed_multiply(vectors[direction * 2], speed);
    vectors++;
    output->y = frame_fixed_multiply(vectors[direction * 2], speed);
}
