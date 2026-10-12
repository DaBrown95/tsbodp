#include "display.h"
const unsigned short *display_load_background_dma(unsigned int index,
    const struct BackgroundResource *resource, unsigned short tile,
    unsigned short palette, unsigned int x, unsigned int y)
{
    const unsigned short *map = display_load_background_resource_dma(index, resource, tile);
    if (map) display_write_background_map(index, map, tile, palette, x, y);
    return map;
}
