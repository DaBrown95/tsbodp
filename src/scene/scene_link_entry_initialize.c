#include "scene_link_entry_setup.h"

void scene_link_entry_initialize(void)
{
    unsigned char compact = 0;
    int i;

    condition_complete_if_active(1, 2, 1);
    if (!(g_game_flags & 0x20)) {
        g_link_received_join.metadata[0] = 4;
        g_link_entry_offers.records[0].kind = 42;
        do {
            g_link_entry_offers.records[1].kind = frame_random_bounded(23);
        } while (g_link_entry_offers.records[1].kind == 31);
        do {
            g_link_entry_offers.records[2].kind = frame_random_bounded(23);
        } while (g_link_entry_offers.records[1].kind == 31 ||
            g_link_entry_offers.records[1].kind ==
                g_link_entry_offers.records[2].kind);
        for (;;) {
            g_link_entry_offers.records[3].kind = frame_random_bounded(23);
            if (g_link_entry_offers.records[1].kind == 31 ||
                g_link_entry_offers.records[3].kind ==
                    g_link_entry_offers.records[1].kind)
                continue;
            if (g_link_entry_offers.records[3].kind !=
                g_link_entry_offers.records[2].kind)
                break;
        }
    } else {
        i = 0;
        if (i < g_link_received_join.metadata[0]) {
            const int identifier = g_link_received_join.identifier;
            do {
                if (i != identifier)
                    g_link_entry_offers.records[i].kind = 42;
                ++i;
            } while (i < g_link_received_join.metadata[0]);
        }
    }
    /* The original clears exactly these two representation bytes with STRH. */
    g_link_entry_offers.records[0].unknown10 = 0;
    g_link_entry_offers.selected = 0;
    g_scene_request.unknown_10 = 0;
    g_display_scene_frame_objects[0] = 0;
    g_display_scene_frame_objects[10] = 0;
    for (i = 3; i >= 0; --i)
        g_display_scene_frame_objects[6 + i] = 0;
    display_set_mode(0);
    display_enable_layers(0x1000);
    if (!(g_game_flags & 0x20))
        display_show_background(3, g_scene_link_entry_control_unlinked);
    else
        display_show_background(3, g_scene_link_entry_control_linked);
    display_show_background(1, g_scene_link_entry_control1);
    display_fill_background(1, 0);
    {
        unsigned int control = g_scene_link_entry_text_control;
        display_show_background(0, control);
        display_fill_background(0, 0);
        display_text_set_background_control(control);
    }
    display_load_palette_alternate(g_display_menu_palette_data, 0, 16);
    if (!(g_game_flags & 0x20))
        display_load_background(3, &g_scene_link_entry_background_unlinked,
            0, 1, 0, 0);
    else
        display_load_background(3, &g_scene_link_entry_background_linked,
            0, 1, 0, 0);
    display_load_resource_palette(&g_display_menu_palette_resource, 0);
    display_load_background_resource(1, &g_scene_link_entry_background1, 1, 3);
    display_load_resource_palette(&g_scene_link_entry_palette4, 4);
    display_load_resource_palette(&g_scene_link_entry_palette5, 5);
    display_load_resource_palette(&g_scene_link_entry_palette6, 6);
    if (!(g_game_flags & 0x20)) {
        scene_view_load_selected_resource(1, 12, 15, 19, 2,
            (const SceneViewResourceSelectionByte *)
            ((const unsigned char *)&g_save_world_view + 0x20));
        display_text_select_font(3, 0, 0);
        display_text_draw_line(35, 23, 118, display_scene_lookup_text(445), 0);
        display_text_draw_line(53, 23, 138, display_scene_lookup_text(446), 0);
        scene_link_entry_refresh_offers_original();
        scene_link_entry_build_objects_original();
    } else {
        i = 0;
        if (i < g_link_received_join.metadata[0]) {
            unsigned int tile_word = 19u << 16;
            for (; i < g_link_received_join.metadata[0]; ++i) {
                if (i != g_link_received_join.identifier) {
                    scene_view_load_selected_resource(1,
                        g_scene_link_selection_captions[compact].x,
                        g_scene_link_selection_captions[compact].y,
                        tile_word >> 16,
                        g_scene_link_selection_palettes[compact],
                        (const SceneViewResourceSelectionByte *)
                        ((const unsigned char *)&g_link_received_join +
                            0x54 + 8 * i));
                    ++compact;
                } else {
                    scene_view_load_selected_resource(1, 3, 1,
                        tile_word >> 16, 2,
                        (const SceneViewResourceSelectionByte *)
                        ((const unsigned char *)&g_link_received_join +
                            0x54 + 8 * i));
                }
                tile_word += 16u << 16;
            }
        }
        display_text_select_font(3, 0, 0);
        display_text_draw_line(35, 22, 128, display_scene_lookup_text(445), 0);
        display_text_draw_line(53, 22, 148, display_scene_lookup_text(446), 0);
        scene_link_entry_refresh_linked_offers();
        scene_link_entry_build_linked_objects();
    }
    scene_link_entry_prepare_original();
    display_time_step_countdown();
    if (!(g_game_flags & 0x20))
        scene_link_entry_draw_quantities();
    else
        scene_link_entry_draw_linked_quantities_original();
    scene_link_entry_draw_panel_original();
    if (!(g_game_flags & 0x20))
        transition_run_first(63, 0);
    else
        transition_fade_black_in_record(63);
}
/* The retained original has two zero alignment bytes before the step entry. */
asm(".align 2, 0");
