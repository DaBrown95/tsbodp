#include "display_text_map.h"

void display_text_fill_map_span(int first, int row, int last, unsigned short tile)
{
    if (first <= last) {
        unsigned short value;
        unsigned short *destination = g_display_text_state.map + (row * 32 + first);
        int bytes = (int)(((unsigned int)last - (unsigned int)first + 1) << 1);
        value = tile;
        DISPLAY_TEXT_DMA->source = (unsigned int)&value;
        DISPLAY_TEXT_DMA->destination = (unsigned int)destination;
        DISPLAY_TEXT_DMA->control = (bytes >> 1) | 0x81000000;
        (void)DISPLAY_TEXT_DMA->control;
    }
}
