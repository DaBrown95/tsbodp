#include "scene_text_bank.h"
void scene_text_bank_initialize(void)
{
    struct SceneRequest *request = &g_scene_request;
    unsigned int i;
    request->parameter = g_save_stream_state.header.bytes[10];
    display_set_mode(0);
    display_configure_tile_allocation(0);
    display_enable_layers(0x1000);
    display_show_background(3, g_scene_text_bank_control);
    display_fill_background_map(3, 0, 52);
    display_fill_background_rectangle(3, 4, 4, 9, 7, 1);
    display_fill_background_rectangle(3, 20, 4, 9, 7, 1);
    display_fill_background_rectangle(3, 4, 20, 9, 7, 1);
    display_fill_background_rectangle(3, 20, 20, 9, 7, 1);
    display_set_background_velocity(3, -65536, -65536);
    display_load_resource_palette(&g_scene_text_bank_palette_resource, 1);
    scene_text_bank_load_preview(request->parameter);
    display_load_palette_alternate(g_scene_text_bank_palette, 0, 16);
    for (i = 0; i <= 5; i++)
        scene_text_bank_create_row(i);
    if (g_scene_previous_request.unknown_00 == 0)
        transition_run_first(63, 1);
    else
        transition_run_first(63, 0);
}
asm(".align 2,0");
