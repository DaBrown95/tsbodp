#include "frame.h"
#include "view_configuration.h"

void transition_get_view_dimensions(struct FramePoint *dimensions,
                                    unsigned char index)
{
    dimensions->x = g_resource_view_dimensions[index].x;
    dimensions->y = g_resource_view_dimensions[index].y;
}
