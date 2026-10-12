#include "display_text_raster.h"

unsigned short *display_text_map_position(unsigned short *map, int x, int y)
{
    y /= 8;
    x /= 8;
    return map + (y * 32 + x);
}
