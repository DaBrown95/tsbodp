#include "scene_default_menu.h"

void scene_default_menu_initialize(void)
{
    unsigned int i;

    audio_select_sequence(0);
    g_frame_flags &= 0xffefffffu;
    save_world_reset_defaults();
    for (i = 0; i < 4; ++i)
        g_scene_default_menu_options[i] = g_scene_default_menu_option_defaults[i];
    {
        unsigned int slot;

        for (slot = 0; slot < 4; ++slot) {
            if (g_save_stream_state.valid[slot] &&
                g_save_stream_state.records[slot].unknown10[0]) {
                g_scene_default_menu_options[1] = 1;
                break;
            }
        }
    }
    if (!g_scene_request.mode)
        g_scene_request.unknown_10 = g_scene_request.mode;
    else
        g_scene_request.unknown_10 = 1;
    g_scene_request.scene = 0;
    g_scene_link_menu_selector_word = g_scene_request.unknown_00;
    g_frame_flags &= 0xfff8d7c7u;
    g_link_flags = 0;
    scene_stage_0803e3a8();
    if (!(g_scene_previous_request.unknown_00 == 6 ||
          g_scene_previous_request.unknown_00 == 19 ||
          g_scene_previous_request.unknown_00 == 7 ||
          g_scene_previous_request.unknown_00 == 10)) {
        display_set_mode(0);
        display_configure_tile_allocation(0);
        display_enable_layers(4096);
        display_configure_background(2, g_scene_default_menu_control2);
        display_load_background(2, &g_scene_default_menu_background2, 1, 0, 0, 0);
        display_load_background_dma(2,
            g_scene_default_menu_text_backgrounds[display_text_selected_bank()],
            228, 0, 8, 2);
        display_show_background(0, g_scene_default_menu_control0);
        display_load_resource_palette(&g_scene_default_menu_palette, 0);
        display_enable_background(2);
        display_hide_background(1);
    } else {
        display_set_mode(0);
        display_configure_tile_allocation(0);
        display_enable_layers(4096);
        scene_default_menu_prepare_background();
    }
    display_text_set_background_control(g_scene_default_menu_control0);
    display_fill_background(0, 0);
    display_load_palette_ranges(&g_scene_default_menu_palette_ranges);
    if (!g_scene_request.unknown_10) {
        const char *text = display_scene_lookup_text(12);

        display_text_select_font(3, 3, 0);
        display_text_draw_line(21, 120, 128, text, 1);
    } else {
        unsigned char slot;

        for (slot = 0; slot < 4; ++slot)
            scene_default_menu_draw_row(slot, g_scene_request.scene);
    }
    transition_run_first(63, 0);
    scene_default_menu_original_setup_objects();
    g_scene_request.scene = 0;
}
