#include "display.h"
#include "display_map_fill.h"

void display_fill_background_constant_rectangle(unsigned int index, int x, int y,
                                                 int width, int height,
                                                 unsigned int tile)
{
    unsigned short tile_value;
    struct BackgroundState *background;
    tile_value = (unsigned short)tile;
    background = &g_background_states[index];
    display_write_constant_map_rectangle(background->tilemap_destination,
                                         x, y, width, height, tile_value);
}
