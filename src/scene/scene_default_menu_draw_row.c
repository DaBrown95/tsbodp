#include "scene_default_menu.h"

void scene_default_menu_draw_row(unsigned int row, unsigned int selected)
{
    unsigned int color;
    unsigned int position;
    unsigned int x, y;
    const char *text;

    if (row == selected)
        color = 3;
    else {
        unsigned int enabled = g_scene_default_menu_options[row];

        color = 12;
        if (enabled)
            color = 0;
    }
    position = row * 16;
    x = (position - row) * 2 + 21;
    y = position + 91;
    text = display_scene_lookup_text(row + 13);
    display_text_select_font(3, color, -1);
    display_text_draw_line(x, 120, y, text, 1);
}
