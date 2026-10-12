#include "frame_layer.h"

unsigned int frame_layer_at_position(unsigned int raw_x, unsigned int raw_y)
{
    struct FramePoint dimensions;
    unsigned int x, y;
    unsigned int cell;
    {
        unsigned int saved_y = raw_y;
        register unsigned int saved_x asm("r4") = raw_x;
        frame_get_map_dimensions(&dimensions);
        y = saved_y;
        x = saved_x;
    }
    if (x > dimensions.x || y > dimensions.y)
        return 3;
    cell = g_frame_layer_blocks[(x >> 5) + (y >> 5) * (dimensions.x >> 5)] << 4;
    cell += ((x >> 3) & 3) | ((y >> 1) & 12);
    return (g_frame_layer_cells[cell] >> 6) + 2;
}
