#include "scene_link_entry_setup.h"
#include "input.h"
#include "resource_actor_entries.h"
void scene_link_entry_step(void)
{
    struct EventPayload payload;
    struct SceneRequest *state;
    unsigned int phase;
    if (g_link_flags & 0x8000) {
        resource_submit_scene(1, 2, g_scene_id);
        g_input_config.player_count = 1;
        g_input_config.local_player = 0;
        return;
    }
    state = &g_scene_request;
    phase = state->unknown_10;
    if (phase == 1) {
        display_time_step_countdown();
        if (!(g_game_flags & 0x20)) {
            scene_link_entry_step_offers();
            scene_link_entry_draw_quantities();
        } else {
            scene_link_entry_step_linked_offers();
            scene_link_entry_draw_linked_quantities();
        }
        if ((unsigned char)display_time_equal(&g_display_countdown,
                &g_resource_selector_clock, 31)) {
            if (!(g_game_flags & 0x20)) {
                display_scene_hide_entry_objects();
                scene_link_entry_confirm_offer();
            } else {
                display_scene_hide_entry_objects();
                display_text_draw_all_lines(71, 165, 16, 136,
                    display_scene_lookup_text(449), 1);
                if (event_get_link_slot() == g_link_received_join.identifier)
                    display_text_draw_all_lines(191, 165, 64, 136,
                        display_scene_lookup_text(227), 1);
                else
                    display_text_draw_all_lines(191, 165, 64, 136,
                        display_scene_lookup_text(225), 1);
                audio_select_sequence(61);
            }
            g_scene_request.unknown_10 = 2;
        } else if (g_game_flags & 0x20) {
            int i;
            for (i = 0; i < g_link_received_join.metadata[0]; ++i) {
                if (i != g_link_received_join.identifier) {
                    int reference_total =
                        g_link_entry_offers.records[g_link_received_join.identifier].count *
                            g_link_entry_offers.multiplier +
                            g_link_entry_offers.records[g_link_received_join.identifier].cost;
                    if (g_link_entry_offers.records[i].count * g_link_entry_offers.multiplier +
                            g_link_entry_offers.records[i].cost >= reference_total) {
                    g_link_entry_offers.selected = i;
                    if (event_get_link_slot() == g_link_entry_offers.selected) {
                        payload.storage.no_payload = (struct EventNoPayload){};
                        if (!(unsigned char)actor_entry_is_full(g_link_entry_game_state.entries))
                            transition_record_event(12, payload);
                        else
                            transition_record_event(13, payload);
                    }
                    g_scene_request.unknown_10 = 2;
                    break;
                    }
                }
            }
        }
    } else if (phase == 0) {
        unsigned short *pressed_base;
        unsigned int input_index;
        if (!(g_game_flags & 0x20)) {
            pressed_base = g_input_pressed;
            input_index = (unsigned int)g_input_config.local_player;
        } else {
            pressed_base = g_input_pressed;
            input_index = (unsigned int)g_link_received_join.identifier;
        }
        if (pressed_base[input_index] & 1) {
            display_fill_background_constant_rectangle(0, 9, 0, 21, 14, phase);
            state->unknown_10 = 1;
            audio_select_sequence(14);
        }
    } else if (phase == 2) {
        if (!(g_game_flags & 0x20)) {
            if (g_input_pressed[g_input_config.local_player] & 1)
                resource_submit_scene(21, 1, 0);
        } else {
            if (g_input_pressed[g_link_received_join.identifier] & 1)
                resource_submit_scene(16, 2, 0);
        }
        if (g_audio_control.flags & 2)
            audio_select_sequence(2);
    }
}
