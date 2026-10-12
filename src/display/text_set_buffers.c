#include "display_text_raster.h"

void display_text_set_buffers(void *map, void *tiles, unsigned int wide_color)
{
    g_display_text_state.map = map;
    g_display_text_state.map_current = map;
    g_display_text_state.tiles = tiles;
    g_display_text_state.tile_bytes = (wide_color + 1) << 5;
    g_display_text_state.wide_color = wide_color;
}
