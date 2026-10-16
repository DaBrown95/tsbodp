#include "frame_actor_24420.h"

int frame_approximate_vector_length(struct FramePoint value)
{
    value.x = value.x < 0 ? -value.x : value.x;
    value.y = value.y < 0 ? -value.y : value.y;
    {
        int result;
        if (value.x > value.y)
            result = ((3 * value.y) >> 3) + value.x;
        else
            result = ((3 * value.x) >> 3) + value.y;
        return result;
    }
}
asm(".align 2,0");
