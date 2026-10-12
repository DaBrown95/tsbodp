#include "display.h"
void display_write_map_palette_rectangle(void *map, int x, int y, int width,
    int height, unsigned short input_palette)
{
    register unsigned short palette asm("r12") = input_palette;
    register int row asm("r2");
    register int column asm("r2");
    int next_row;
    unsigned short *destination;
    for (row = 0; row < height; row = next_row) {
        destination = (unsigned short *)((unsigned int)map + (y + row) * 64 + x * 2);
        next_row = row + 1;
        if (width > 0) {
            unsigned int palette_bits = palette << 12;
            column = width;
            do {
                unsigned int tile = *destination;
                tile = (tile << 20) >> 20;
                *destination = tile + palette_bits;
                ++destination;
                --column;
            } while (column);
        }
    }
}
__asm__(".align 2, 0");
