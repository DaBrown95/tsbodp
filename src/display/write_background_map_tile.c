#include "display_map.h"

void display_write_background_map_tile(unsigned int index, int x, int y,
    unsigned int tile, unsigned int palette)
{
    struct DisplayMapState *background = &g_display_map_states[index];
    unsigned short *destination = background->map + y * 32 + x;
    *destination = (palette << 12) + tile;
    background->flags |= 0x20;
}
