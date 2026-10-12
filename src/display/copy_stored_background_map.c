#include "display_map.h"

void display_copy_stored_background_map(unsigned int index, int width, int height,
    int source_x, int source_y, int destination_x, int destination_y)
{
    register int rows __asm__("r2") = height;
    struct DisplayMapState *background = &g_display_map_states[index];
    int stride = background->stored_map->width;
    const unsigned short *source = background->stored_map->tiles;
    unsigned short *destination = background->destination;
    source += source_y * stride + source_x;
    destination += destination_y * 32 + destination_x;
    if (rows > 0) {
        int source_skip = stride - width;
        int destination_skip = 32 - width;
    do {
        int count = width;
        --rows;
        while (count > 0) {
            *destination++ = *source++;
            --count;
        }
        source += source_skip;
        destination += destination_skip;
    } while (rows > 0);
    }
    background->flags |= 0x20;
}
