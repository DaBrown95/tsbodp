#include "display_condition_panel.h"

void condition_panel_draw_row_labels(unsigned int selected)
{
    unsigned int index;
    unsigned int tile = 71;
    for (index = 0; index <= 4; ++index) {
        unsigned int style;
        display_text_number_field_zero(index + 1);
        if (selected == index) {
            if (g_display_scene_request_state.mode == 0) {
                style = 3;
                g_condition_panel_objects[9]->id = index + 77;
                frame_set_variant_state(g_condition_panel_objects[9], 58);
            } else {
                style = 9;
            }
        } else {
            unsigned int limit = g_condition_panel_world.row;
            style = index <= limit ? 0 : 11;
        }
        display_text_select_font(1, style, -1);
        tile = display_text_draw_line(tile,
            g_condition_panel_label_coordinates[index].x,
            g_condition_panel_label_coordinates[index].y,
            display_scene_lookup_text(6222), 0);
    }
}
asm(".align 2, 0");
