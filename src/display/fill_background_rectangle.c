#include "display.h"
void display_fill_background_rectangle(unsigned int index, int x, int y, int width, int height,
                                       unsigned short tile)
{
    struct BackgroundState *background = &g_background_states[index];
    display_write_incrementing_map_rectangle(background->tilemap_destination,
                                             x, y, width, height, tile);
}
