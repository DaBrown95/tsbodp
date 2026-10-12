#include "display_text_raster.h"

void display_text_emit_rows(const unsigned int *source, unsigned int rows,
                            unsigned short *map, void *tiles, unsigned int tile)
{
    --rows;
    while (rows != -1U) {
        unsigned int *destination = (void *)((unsigned char *)tiles + tile * g_display_text_state.tile_bytes);
        unsigned int words = g_display_text_state.tile_bytes >> 2;
        --words;
        while (words != -1U) {
            *destination++ = *source++;
            --words;
        }
        if (g_display_text_state.wide_color == 1) *map = tile;
        else if (g_display_text_state.fill == -1) *map = (*map & 0xf000) | tile;
        else *map = g_display_text_state.palette_bits | tile;
        map += 32;
        ++tile;
        --rows;
    }
}

__asm__(".align 2, 0");
