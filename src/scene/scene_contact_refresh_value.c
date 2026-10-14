#include "scene_contact_menu.h"
void scene_contact_refresh_value(void)
{
    if (g_scene_contact_state->flags & 8) {
        const struct DisplayCountdownSceneLayout *layouts =
            g_scene_contact_value_layouts;
        const char *text;
        display_clear_background_rectangle(0,
            layouts[g_scene_contact_state->scene].left,
            layouts[g_scene_contact_state->scene].top,
            layouts[g_scene_contact_state->scene].width,
            layouts[g_scene_contact_state->scene].height);
        display_text_select_font(3, 0, 0);
        display_text_number_field_zero(g_scene_contact_state->amount);
        text = display_scene_lookup_text(6220);
        display_text_draw_line(19,
            layouts[g_scene_contact_state->scene].x,
            layouts[g_scene_contact_state->scene].y, text, 1);
        g_scene_contact_state->flags &= ~8;
    }
}
