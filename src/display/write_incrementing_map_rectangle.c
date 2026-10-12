#include "display.h"
void display_write_incrementing_map_rectangle(void *map, int x, int y, int width, int height,
                                             unsigned short tile)
{
    register int row __asm__("r1");
    int column, next_row;
    unsigned short *destination;
    for (row = 0; row < height; row = next_row) {
        destination = (unsigned short *)((unsigned int)map + (y + row) * 64 + x * 2);
        next_row = row + 1;
        if (width > 0) {
            column = width;
            do {
                *destination++ = tile;
                ++tile;
                --column;
            } while (column);
        }
    }
}
__asm__(".align 2, 0");
