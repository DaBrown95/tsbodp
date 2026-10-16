#include "scene_link_entry_setup.h"

void scene_link_entry_draw_header_value(void)
{
    if (!(g_game_flags & 0x20)) {
        display_text_select_font(3, 0, 0);
        display_text_number_field_zero(g_save_world_view.unknown04);
        display_fill_background_constant_rectangle(0, 2, 1, 7, 2, 0);
        display_text_draw_line(1, 48, 14, display_scene_lookup_text(6220), 1);
    } else {
        display_text_select_font(3, 0, 0);
        display_text_number_field_zero(g_save_world_view.unknown04);
        display_fill_background_constant_rectangle(0, 2, 6, 7, 2, 0);
        display_text_draw_line(1, 48, 52, display_scene_lookup_text(6220), 1);
    }
}
