#include "display_text_raster.h"

void display_text_fill_rows(unsigned int *destination, unsigned int rows, unsigned int color)
{
    unsigned int words;
    if (g_display_text_state.wide_color == 1) {
        color += (color << 24) + (color << 16) + (color << 8);
        words = rows * 16;
    } else {
        color &= 15;
        color += color << 4;
        color += color << 8;
        color += color << 16;
        words = rows * 8;
    }
    --words;
    while (words != -1U) {
        *destination++ = color;
        --words;
    }
}

__asm__(".align 2, 0");
