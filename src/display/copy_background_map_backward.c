#include "display_map.h"

void display_copy_background_map_backward(unsigned int index, int width, int height,
    int source_x, int source_y, int destination_x, int destination_y)
{
    register int rows __asm__("r2") = height;
    struct DisplayMapState *background = &g_display_map_states[index];
    unsigned short *source = background->buffer + (source_y + rows - 1) * 32 + source_x + width - 1;
    unsigned short *destination = background->buffer + (destination_y + rows - 1) * 32 + destination_x + width - 1;
    while (rows > 0) {
        int count = width;
        --rows;
        while (count > 0) {
            *destination-- = *source--;
            --count;
        }
        source += width - 32;
        destination += width - 32;
    }
    background->flags |= 0x20;
}
