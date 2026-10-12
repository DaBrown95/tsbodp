#include "display.h"
void display_fill_background_map(unsigned int index, unsigned short tile, unsigned short palette)
{
    struct BackgroundState *background = &g_background_states[index];
    unsigned short fill;
    unsigned int count;
    display_fill_background_tile(index, tile, palette);
    if (!(*(unsigned char *)background & 0x80))
        tile |= (palette >> 4) << 12;
    count = g_display_screen_block_counts[((unsigned char *)background)[1] >> 6];
    fill = tile;
    display_cpu_copy(&fill, background->tilemap_buffer, (count << 10) | 0x01000000);
    background->flags |= 0x20;
}
