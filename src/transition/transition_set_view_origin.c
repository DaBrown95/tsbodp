#include "view_effects.h"
void transition_set_view_origin(struct FramePoint point,unsigned char index)  {
    g_resource_view_motion[index].position.x=point.x;
    g_resource_view_motion[index].position.y=point.y;
}
