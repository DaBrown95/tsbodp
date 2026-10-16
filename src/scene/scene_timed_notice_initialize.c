#include "scene_timed_notice.h"
void scene_timed_notice_initialize(void)
{
    unsigned int tile = 1;
    unsigned int control0;
    display_set_mode(0);
    display_show_background(3, g_scene_timed_notice_control3);
    display_load_background(3, &g_scene_timed_notice_background, 0, 1, 0, 0);
    control0 = g_scene_timed_notice_control0;
    display_show_background(0, control0);
    display_fill_background(0, 0);
    display_load_resource_palette(&g_display_menu_palette_resource, 0);
    display_text_set_background_control(control0);
    display_text_select_font(3, 9, 0);
    tile = display_text_draw_all_lines(tile, 120, 56, 224,
                                     display_scene_lookup_text(0), 1);
    display_text_draw_all_lines(tile, 120, 136, 240,
                               display_scene_lookup_text(2), 1);
    transition_run_first(63, 1);
    audio_select_sequence(0);
    game_start_countdown_slot(0, 60);
    game_start_countdown_slot(1, 90);
}
