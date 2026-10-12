#include "display_map.h"

void display_copy_map_rectangle(int width, int height, int source_x, int source_y,
    int source_stride, const unsigned short *source, int destination_x,
    int destination_y, int destination_stride, unsigned short *destination)
{
    int rows;

    source += source_y * source_stride + source_x;
    destination += destination_y * destination_stride + destination_x;
    rows = height;
    while (rows > 0) {
        int count = width;
        int next_rows = rows - 1;
        while (count > 0) {
            *destination++ = *source++;
            --count;
        }
        source += source_stride - width;
        destination += destination_stride - width;
        rows = next_rows;
    }
}

__asm__(".align 2, 0");
