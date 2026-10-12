#include "display_text_raster.h"

unsigned int display_text_draw_block(unsigned int tile, int x, int y, int width,
                                    int height, const char **text, unsigned int style)
{
    unsigned int limit = 0x7fffffff;
    while (**text && height >= g_display_text_state.line_height) {
        tile = display_text_draw(tile, x, y, width, text, style, &limit);
        y += g_display_text_state.line_height;
        height -= g_display_text_state.line_height;
    }
    return tile;
}
