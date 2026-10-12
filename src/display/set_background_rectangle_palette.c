#include "display.h"
void display_set_background_rectangle_palette(unsigned int index, int x, int y, int width, int height,
                                       unsigned short palette)
{
    struct BackgroundState *background = &g_background_states[index];
    display_write_map_palette_rectangle(background->tilemap_destination,
                                             x, y, width, height, palette);
}
