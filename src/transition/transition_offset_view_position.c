#include "view_effects.h"

void transition_offset_view_position(struct FramePoint delta, unsigned char index)
{
    g_resource_view_motion[index].position.x += delta.x;
    g_resource_view_motion[index].position.y += delta.y;
    g_resource_view_motion[index].target = g_resource_view_motion[index].position;
}
