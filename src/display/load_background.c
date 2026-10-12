#include "display.h"
const unsigned short *display_load_background(unsigned int index,
    const struct BackgroundResource *resource, unsigned short tile,
    unsigned short palette, unsigned int x, unsigned int y)
{
    const unsigned short *map = display_load_background_resource(index, resource, tile, palette);
    if (map) display_write_background_map(index, map, tile, palette, x, y);
    return map;
}
__asm__(".align 2, 0");
