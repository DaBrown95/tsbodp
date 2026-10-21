#include "frame.h"
#include "view_configuration.h"

void transition_set_view_dimensions(const struct FramePoint *dimensions,
                                    unsigned char index)
{
    g_resource_view_dimensions[index].x = dimensions->x;
    g_resource_view_dimensions[index].y = dimensions->y;
}
