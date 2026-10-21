#include "view_effects.h"
#include "frame_map.h"

void transition_get_view_origin_delta(struct FramePoint *point, unsigned char index)
{
    frame_get_view_origin(point, index);
    point->x = (short)(g_resource_view_motion[index].position.x >> 16) - point->x;
    point->y = (short)(g_resource_view_motion[index].position.y >> 16) - point->y;
}
