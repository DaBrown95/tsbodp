#include "scene_row24_selection_private.h"

void scene_row24_selection_draw_lines(unsigned int *tile, int x, int *y,
                                      const char *text)
{
    unsigned int remaining = 0x7fffffff;

    while (*text) {
        *tile = display_text_draw(*tile, x, *y, 148, &text, 0, &remaining);
        *y += 12;
    }
}
