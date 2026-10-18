#include "scene_link_entry_setup.h"

void scene_link_entry_confirm_offer(void)
{
    display_text_select_font(1, 3, 0);
    display_scene_hide_entry_objects();
    audio_game_stop_sequence();
    audio_select_sequence(2);
    if (g_link_entry_effect_state.records[g_link_entry_effect_state.selected].kind == 42) {
        int amount;
        actor_entry_add(g_link_entry_game_state.entries,
            g_scene_request.scene, (unsigned char)g_scene_request.parameter,
            (g_scene_request.parameter & 0xff00) >> 8);
        amount = (g_link_entry_effect_state.records[g_link_entry_effect_state.selected].count *
            g_link_entry_effect_state.multiplier +
            g_link_entry_effect_state.records[g_link_entry_effect_state.selected].cost) >> 16;
        g_link_entry_game_state.amount -= amount;
        display_text_copy_field_zero((const char *)&g_link_entry_game_state + 16);
        audio_play_sequence_notification(60);
    } else {
        display_text_copy_field_zero(display_scene_lookup_text(
            g_link_entry_effect_state.records[g_link_entry_effect_state.selected].kind + 0x1789));
        audio_play_sequence_notification(61);
    }
    display_text_draw_all_lines(71, 165, 16, 136, display_scene_lookup_text(447), 1);
    display_text_draw_all_lines(191, 165, 64, 136, display_scene_lookup_text(227), 1);
}
