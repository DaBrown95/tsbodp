#include "scene_link_menu_actions.h"
void scene_link_menu_draw_row(unsigned int row, unsigned int selected)
{
    register unsigned int mode asm("r6");
    unsigned int tile;
    int y;
    const char *text;
    {
        unsigned int font_color;
        font_color = 0;
        if (row == selected)
            font_color = 3;
        display_text_select_font(3, font_color, 0);
    }
    mode = g_scene_request.unknown_10;
    if (mode == 1) {
        tile = (row + 1) * 64 + 1;
        y = row * 22 + 44;
        text = display_scene_lookup_text(row + 210);
        display_text_draw_line(tile, 120, y, text, mode);
    } else {
        tile = row * 64 + 1;
        if (!(g_frame_flags & 0x20) && !(g_link_flags & 0x8000))
            y = row * 22 + 28;
        else
            y = row * 22 + 64;
        text = display_scene_lookup_text(row + 213);
        display_text_draw_line(tile, 120, y, text, 1);
    }
}
asm(".align 2,0");
