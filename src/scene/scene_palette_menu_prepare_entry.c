#include "scene_palette_menu_entry.h"

void scene_palette_menu_prepare_entry(void)
{
    display_fill_background(0, 0);
    display_fill_background(1, 0);
    display_fill_background(2, 0);
    display_text_select_font(1, 0, -1);
    display_load_background(2, &g_palette_menu_entry_background2, 18, 2, 0, 0);
    display_load_background(1, &g_palette_menu_entry_background1, 58, 3, 0, 0);
    display_load_palette(g_frame_actor_palette_menu_entry_palette, 64, 16);
    display_text_draw_template(1, 37, g_palette_menu_entry_template);
    display_set_background_scroll_target(0, 0, -160 * 65536, 1);
    display_set_background_scroll_target(1, 0, -160 * 65536, 1);
    display_set_background_scroll_target(2, 0, 176 * 65536, 1);
    scene_palette_menu_build_entry_objects();
}

asm(".align 2,0");
