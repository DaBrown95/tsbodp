#include "display_text_draw.h"
#include "display_text_measure_inline.h"

unsigned int display_text_draw_line(unsigned int tile, int input_x, int input_y,
                                   const char *input, unsigned int style)
{
    const char *text = input;
    int x = input_x, y = input_y;
    if (style == 1) x -= (display_text_width_inline(text) + 1) / 2;
    else if (style == 2) x -= display_text_width_inline(text);
    if (style == 4) y -= (display_text_height_inline(text) + 1) / 2;
    else if (style == 8) y -= display_text_height_inline(text);
    return display_text_render(tile, x, y, text);
}
