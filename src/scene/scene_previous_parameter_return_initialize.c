#include "scene_previous_parameter_return.h"

void scene_previous_parameter_return_initialize(void)
{
    int y = 5;
    unsigned int tile = 1;
    unsigned int limit = 0x7fffffff;
    const char *text;
    unsigned int control;

    display_set_mode(0);
    display_configure_tile_allocation(0);
    display_enable_layers(4096);
    display_show_background(3, g_scene_previous_parameter_return_control3);
    display_load_background(3,
        &g_scene_previous_parameter_return_background3, 0, 0, 0, 0);
    control = g_scene_previous_parameter_return_control0;
    display_show_background(0, control);
    display_fill_background(0, 0);
    display_load_resource_palette(&g_scene_previous_parameter_return_palette, 0);
    display_text_set_background_control(control);
    display_text_select_font(3, 0, -1);
    text = display_scene_lookup_text(308);
    while (*text) {
        tile = display_text_draw(tile, 156, y, 158, &text, 1, &limit);
        y += 12;
    }
    transition_run_first(63, 0);
    audio_play_sequence_notification(54);
}
asm(".align 2,0");
