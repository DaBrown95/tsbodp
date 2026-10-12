#include "display_text_raster.h"

unsigned int display_text_draw_limited_line(unsigned int tile, int x, int y, int width,
                                          int height, const char **text,
                                          unsigned int style, unsigned int *limit)
{
    if (**text && height >= g_display_text_state.line_height)
        tile = display_text_draw(tile, x, y, width, text, style, limit);
    return tile;
}
