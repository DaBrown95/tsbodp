#include "display_map.h"

void display_copy_background_map_forward(unsigned int index, int width, int height,
    int source_x, int source_y, int destination_x, int destination_y)
{
    register int rows __asm__("r2") = height;
    struct DisplayMapState *background = &g_display_map_states[index];
    unsigned short *source = background->buffer + source_y * 32 + source_x;
    unsigned short *destination = background->buffer + destination_y * 32 + destination_x;
    while (rows > 0) {
        int count = width;
        --rows;
        while (count > 0) {
            *destination++ = *source++;
            --count;
        }
        source += 32 - width;
        destination += 32 - width;
    }
    background->flags |= 0x20;
}
