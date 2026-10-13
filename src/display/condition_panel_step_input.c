#include "display_condition_panel_input.h"

void condition_panel_step_input(void)
{
    if (g_input_pressed[g_input_config.local_player] & 0xf0) {
        if (g_input_local_pressed[g_input_config.local_player] & 0x80) {
            struct DisplaySceneRequestState *state = &g_display_scene_request_state;
            if (state->mode == 0) {
                state->mode = 1;
                condition_panel_draw_details(state->parameter, state->scene);
                condition_panel_draw_row_labels(state->parameter);
                g_condition_panel_objects[8]->flags |= 1;
            }
        } else if (g_input_local_pressed[g_input_config.local_player] & 0x40) {
            struct DisplaySceneRequestState *state = &g_display_scene_request_state;
            if (state->mode == 1) {
                state->mode = 0;
                condition_panel_draw_row_labels(state->parameter);
                g_condition_panel_objects[8]->flags &= ~1;
            }
        }
        if (g_input_local_pressed[g_input_config.local_player] & 0x20) {
            struct DisplaySceneRequestState *state = &g_display_scene_request_state;
            if (state->mode == 1) {
                if (state->scene != 0) {
                    --state->scene;
                    condition_panel_draw_details(state->parameter, state->scene);
                    g_condition_panel_objects[8]->id = state->scene + 82;
                    frame_set_variant_state(g_condition_panel_objects[8], 58);
                }
            } else if (state->parameter != 0) {
                --state->parameter;
                condition_panel_draw_row_labels(state->parameter);
                condition_panel_update_column_objects(state->parameter);
                condition_panel_draw_details(state->parameter, state->scene);
            }
        } else if (g_input_local_pressed[g_input_config.local_player] & 0x10) {
            struct DisplaySceneRequestState *state = &g_display_scene_request_state;
            if (state->mode == 1) {
                if (state->scene != 5) {
                    ++state->scene;
                    condition_panel_draw_details(state->parameter, state->scene);
                    g_condition_panel_objects[8]->id = state->scene + 82;
                    frame_set_variant_state(g_condition_panel_objects[8], 58);
                }
            } else if (state->parameter < g_condition_panel_world.row) {
                ++state->parameter;
                condition_panel_draw_row_labels(state->parameter);
                condition_panel_update_column_objects(state->parameter);
                condition_panel_draw_details(state->parameter, state->scene);
            }
        }
        audio_play_animation_cue(0);
    }
    if (g_input_local_pressed[g_input_config.local_player] & 0x100) {
        ((struct ConditionPanelExitView *)&g_condition_panel_world)->code = 17;
        scene_submit_default_request(17);
        audio_play_animation_cue(11);
    } else if (g_input_local_pressed[g_input_config.local_player] & 0x200) {
        ((struct ConditionPanelExitView *)&g_condition_panel_world)->code = 16;
        scene_submit_default_request(16);
        audio_play_animation_cue(11);
    } else if (g_input_pressed[g_input_config.local_player] & 0xa) {
        resource_submit_scene(1, 2, g_condition_panel_return_arg);
        audio_play_animation_cue(2);
    }
}
asm(".align 2, 0");
