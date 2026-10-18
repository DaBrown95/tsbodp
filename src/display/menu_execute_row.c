#include "display_menu_results.h"
#include "display_window.h"

static inline unsigned int selected_result_text(void)
{
    const unsigned short *ids = g_display_menu_result_descriptors[g_display_menu_state.definition].text_ids;
    ids += g_display_menu_result_game.text_variant;
    return *ids +
        g_display_menu_state.parameters[g_display_scene_request_state.scene];
}

void display_menu_execute_row(void)
{
    frame_adjust_actor_needs(&g_display_menu_result_local_needs, 46, 1);
    display_time_step_world(&g_display_menu_result_time_delta);
    display_fill_background(0, 60);
    display_disable_window(0);
    display_enable_window(1);
    {
        struct DisplayMenuState *menu = &g_display_menu_state;
        unsigned char *active = &menu->repeat_delay;
        unsigned int zero = 0;
        *active = zero;
        display_set_background_scroll_target(zero, 0, 0, 1);
        g_display_scene_request_state.unknown_10 = 1;
        switch (menu->codes[g_display_scene_request_state.scene]) {
        case 0:
            display_menu_show_hint(0);
            display_menu_request_notice(16, 1, 0);
            display_menu_stage_result_text(display_scene_lookup_text(selected_result_text()));
            break;
        case 1:
            display_menu_show_hint(1);
            display_menu_stage_result_text(display_scene_lookup_text(selected_result_text()));
            display_menu_reset_result_text();
            break;
        case 2: case 3: case 4: case 5: case 22:
            {
                const char *text;
                if (g_display_menu_state.codes[g_display_scene_request_state.scene] != 22)
                    text = display_scene_lookup_text(selected_result_text());
                else
                    text = display_scene_lookup_text(1152);
                display_menu_stage_result_text(text);
            }
            display_menu_apply_primary_result();
            break;
        case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
        case 14: case 15: case 16: case 17: case 18: case 19: case 20:
            if (!g_display_menu_state.unknown_28)
                display_menu_show_hint(1);
            display_menu_stage_result_text(display_scene_lookup_text(selected_result_text()));
            display_menu_apply_secondary_result();
            break;
        case 21:
            display_menu_show_hint(0);
            display_menu_request_notice(1, 2, g_display_menu_notice_owner);
            audio_play_animation_cue(g_display_menu_result_descriptors[g_display_menu_state.definition].cues[8]);
            audio_play_animation_cue(80);
            display_menu_stage_result_text(display_scene_lookup_text(selected_result_text()));
            break;
        case 23: case 24: case 25: case 26:
            {
                struct DisplayMenuState *current = &g_display_menu_state;
                const struct DisplayMenuTextRecord *const *entry;
                const struct DisplayMenuTextRecord *const *groups;
                unsigned char *choice;
                unsigned int selected;
                const struct DisplayMenuTextRecord *records;
                if (!current->unknown_28)
                    display_menu_show_hint(1);
                groups = g_display_menu_text_records;
                entry = &groups[current->record_group];
                choice = &current->choice;
                selected = *choice;
                records = *entry;
                *choice = records[selected].entries[g_display_scene_request_state.scene];
                display_menu_stage_result_text(display_scene_lookup_text((*entry)[*choice].text));
            }
            display_menu_draw_choice_result();
            break;
        case 27:
            display_menu_show_hint(0);
            display_menu_request_notice(1, 2, g_display_menu_notice_owner);
            audio_play_animation_cue(g_display_menu_result_descriptors[g_display_menu_state.definition].cues[8]);
            audio_play_animation_cue(80);
            display_menu_stage_result_text(display_scene_lookup_text(
                1154 + g_display_menu_state.parameters[g_display_scene_request_state.scene]));
            break;
        case 28:
            display_menu_show_hint(1);
            display_menu_stage_result_text(display_scene_lookup_text(1153));
            display_menu_prepare_state_42();
            break;
        }
    }
}

asm(".align 2, 0");
