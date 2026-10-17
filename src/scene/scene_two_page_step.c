#include "scene_two_page.h"

void scene_two_page_step(void)
{
    unsigned int control;
    const char *text;
    switch (g_scene_request.unknown_10) {
    case 0: {
        unsigned int old_timer;
        old_timer = g_scene_request.unknown_14--;
        if (old_timer == 0) {
            g_scene_request.unknown_10 = 1;
            g_scene_request.unknown_14 = 60;
        } else {
            transition_set_black_brightness(2, g_scene_request.unknown_14);
        }
        break;
    }
    case 1: {
        unsigned int old_timer;
        old_timer = g_scene_request.unknown_14--;
        if (old_timer == 0) {
            g_scene_request.unknown_10 = 2;
            g_scene_request.unknown_14 = 16;
        }
        break;
    }
    case 2: {
        unsigned int old_timer;
        old_timer = g_scene_request.unknown_14--;
        if (old_timer != 0) {
            transition_set_black_brightness(2, 16 - g_scene_request.unknown_14);
        } else {
            transition_set_black_brightness(63, 16);
            if (++g_scene_request.scene != 2) {
                if (g_scene_request.scene == 1) {
                    control = g_scene_text_bank_control;
                    display_show_background(1, control);
                    display_text_set_background_control(control);
                } else {
                    control = g_scene_two_page_default_control;
                    display_show_background(1, control);
                    display_text_set_background_control(control);
                }
                display_fill_background(1, 250);
                display_load_background(1,
                    g_scene_two_page_rows[g_scene_request.scene].resource, 1, 0, 0, 0);
                display_load_resource_palette(&g_display_scrolling_palette, 0);
                display_text_select_font(g_scene_two_page_rows[g_scene_request.scene].font,
                                         0, 0);
                text = display_scene_lookup_text(
                    g_scene_two_page_rows[g_scene_request.scene].text_id);
                display_text_draw_all_lines(250, 120,
                    g_scene_two_page_rows[g_scene_request.scene].text_y, 238, text, 1);
                g_scene_request.unknown_10 = 0;
                g_scene_request.unknown_14 = 16;
            } else {
                g_scene_request.unknown_10 = 3;
            }
        }
        break;
    }
    case 3:
        scene_submit_default_request(5);
        break;
    }
}
