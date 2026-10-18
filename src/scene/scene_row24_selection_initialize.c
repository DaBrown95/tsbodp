#include "scene_row24_selection_private.h"

void scene_row24_selection_initialize(void)
{
    unsigned int control;
    const struct BackgroundResource *palette;

    g_scene_request.scene = 0;
    g_scene_request.parameter = 0;
    display_set_mode(0);
    display_enable_layers(4096);
    display_show_background(3, g_scene_row24_selection_control3);
    display_show_background(2, g_scene_row24_selection_control2);
    display_show_background(1, g_scene_row24_selection_control1);
    display_fill_background(1, 0);
    control = g_scene_row24_selection_control0;
    display_show_background(0, control);
    display_fill_background(0, 0);
    palette = &g_display_scrolling_palette;
    display_load_resource_palette(palette, 0);
    display_load_palette_alternate((const unsigned char *)palette + 2, 0, 16);
    display_load_background(3, &g_display_scrolling_resource3, 0, 4, 0, 0);
    display_set_background_velocity(3, 32768, 32768);
    display_load_background(2, &g_scene_row24_selection_background2, 4, 1, 0, 0);
    display_load_resource_palette(palette, 0);
    display_text_select_font(3, 0, 0);
    display_text_set_background_control(control);
    scene_row24_selection_prepare_original();
    transition_run_first(63, 0);
}
