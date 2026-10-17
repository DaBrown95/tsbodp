#include "scene_two_page.h"

void scene_two_page_initialize(void)
{
    unsigned int control;
    const char *text;
    g_scene_request.scene = 0;
    display_set_mode(0);
    display_configure_tile_allocation(0);
    control = g_scene_two_page_default_control;
    display_show_background(1, control);
    display_fill_background(1, 0);
    display_load_background(1, g_scene_two_page_rows[g_scene_request.scene].resource,
                            1, 0, 0, 0);
    display_load_resource_palette(&g_display_scrolling_palette, 0);
    if (g_scene_request.scene == 1)
        display_text_set_background_control(g_scene_text_bank_control);
    else
        display_text_set_background_control(control);
    display_text_set_background_control(g_scene_two_page_default_control);
    display_text_select_font(g_scene_two_page_rows[g_scene_request.scene].font, 0, 0);
    text = display_scene_lookup_text(g_scene_two_page_rows[g_scene_request.scene].text_id);
    display_text_draw_all_lines(250, 120,
        g_scene_two_page_rows[g_scene_request.scene].text_y, 238, text, 1);
    transition_set_black_brightness(2, 16);
    g_scene_request.unknown_10 = 0;
    g_scene_request.unknown_14 = 16;
}
