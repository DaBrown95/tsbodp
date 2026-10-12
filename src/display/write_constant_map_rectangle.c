#include "display.h"
void display_write_constant_map_rectangle(void *map, int x, int y, int width,
    int height, unsigned short tile)
{
    int row, column;
    unsigned short *destination;
    for (row = 0; row < height; ++row) {
        destination = (unsigned short *)((unsigned int)map + (y + row) * 64 + x * 2);
        if (width > 0) {
            column = width;
            do {
                *destination++ = tile;
                --column;
            } while (column);
        }
    }
}
__asm__(".align 2, 0");
