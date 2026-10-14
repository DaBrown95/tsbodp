#include "scene_link_menu.h"

void scene_link_menu_draw_status(void)
{
    display_fill_background_constant_rectangle(2, 15, 17, 28, 2, 0);
    if (g_link_flags & 0x8000) {
        display_text_select_font(3, 3, 0);
        display_text_draw_line(425, 120, 136, display_scene_lookup_text(222), 1);
    } else {
        display_text_select_font(3, 3, 0);
        display_text_draw_line(425, 120, 136, display_scene_lookup_text(223), 1);
    }
}
asm(".align 2,0");
