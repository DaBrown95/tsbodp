#include "frame.h"

unsigned int frame_points_equal_unrooted_273fc(const struct FramePoint *first,
                                               const struct FramePoint *second)
{
    unsigned int result = 0;
    if (first->x == second->x && first->y == second->y)
        result = 1;
    return result;
}
