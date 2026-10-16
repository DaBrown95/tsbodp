#include "scene_link_entry_setup.h"

void scene_link_entry_draw_panel(void)
{
    char text[128];
    unsigned char variant = g_save_world_view.unknown10[0x18];
    unsigned int text_id;

    display_text_select_font(1, 3, 0);
    if (g_scene_request.scene == 82) {
        switch (variant) {
        case 0: text_id = 599; break;
        case 1: text_id = 606; break;
        case 2: text_id = 600; break;
        case 3: text_id = 609; break;
        case 4: text_id = 603; break;
        case 5: text_id = 601; break;
        case 6: text_id = 604; break;
        case 7: text_id = 610; break;
        case 8: text_id = 605; break;
        case 9: text_id = 607; break;
        case 10: text_id = 608; break;
        case 11: text_id = 602; break;
        default: goto after_field;
        }
        display_text_copy_field_zero(display_scene_lookup_text(text_id));
    } else {
        display_text_copy_field_zero(display_scene_lookup_text(
            g_display_scene_catalog[g_scene_request.scene].text_id));
    }
after_field:
    display_text_copy_expanded((const unsigned char *)display_scene_lookup_text(448), text);
    display_text_draw_all_lines(71, 165, 16, 136, text, 1);
    if (!(g_game_flags & 0x20) ||
        event_get_link_slot() == g_link_received_join.identifier) {
        display_text_draw_all_lines(191, 165, 64, 136,
            display_scene_lookup_text(227), 1);
    } else {
        display_text_draw_all_lines(191, 165, 64, 136,
            display_scene_lookup_text(225), 1);
    }
}
