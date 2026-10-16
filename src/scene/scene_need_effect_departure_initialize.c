#include "frame_need_effect_departure.h"

void scene_need_effect_departure_initialize(void)
{
    display_set_mode(0);
    display_configure_tile_allocation(0);
    display_enable_layers(0x1000);
    display_show_background(3, g_need_effect_departure_control3);
    display_load_background(3, &g_need_effect_departure_background3, 1, 0, 0, 0);
    display_show_background(2, g_need_effect_departure_control2);
    display_load_background(2, &g_need_effect_departure_background2, 484, 0, 0, 0);
    display_load_palette_ranges(&g_need_effect_departure_palette_ranges);
    frame_define_palette_slot(0, g_need_effect_departure_palette_slot);
    frame_create_need_effect_departure();
    transition_run_first(63, 0);
    g_scene_request.scene = 0;
}
