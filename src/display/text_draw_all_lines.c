#include "display_text_raster.h"

unsigned int display_text_draw_all_lines(unsigned int tile, int x, int y, int width,
                                        const char *text, unsigned int style)
{
    unsigned int limit = 0x7fffffff;
    while (*text) {
        tile = display_text_draw(tile, x, y, width, &text, style, &limit);
        y += g_display_text_state.line_height;
    }
    return tile;
}
