#include "display_scene_selector.h"
void display_update_scrolling_scene(void)
{
    int advance = 0;
    struct DisplaySceneRequestState *state = &g_display_scene_request_state;
    unsigned char previous_group;
    switch (state->unknown_10) {
    case 0:
        if (--state->unknown_14 == -1) {
            state->unknown_10 = 1;
            transition_run_first(0x3f, 0);
        }
        break;
    case 1:
        previous_group = state->scene;
        if (g_input_pressed[g_input_config.local_player] & 0x40) {
            if (!display_scene_previous_group())
                audio_play_animation_cue(3);
            if (g_display_scene_owner_link.first_owner->id == 0xb2) {
                g_display_scene_owner_link.first_owner->id = 0xb1;
                frame_set_variant_state((void *)g_display_scene_owner_link.first_owner, 0x3a);
                previous_group = state->scene;
            }
        } else if (g_input_pressed[g_input_config.local_player] & 0x80) {
            if (!display_scene_next_group())
                audio_play_animation_cue(3);
            if (g_display_scene_owner_link.first_owner->id == 0xb1) {
                g_display_scene_owner_link.first_owner->id = 0xb2;
                frame_set_variant_state((void *)g_display_scene_owner_link.first_owner, 0x3a);
                previous_group = state->scene;
            }
        } else if (g_input_pressed[g_input_config.local_player] & 0x20) {
            audio_play_animation_cue(3);
        } else if (g_input_pressed[g_input_config.local_player] & 0x10) {
            advance = 1;
            audio_play_animation_cue(0);
        }
        if (previous_group != g_display_scene_request_state.scene)
            display_scene_stage_0800f29c(previous_group);
        break;
    case 2:
        if (g_input_pressed[g_input_config.local_player] & 0x20) {
            if (!state->parameter)
                advance = 1;
            else {
                --state->parameter;
                g_display_scene_owner_link.owner->id = 0xb8 + state->parameter;
                frame_set_variant_state((void *)g_display_scene_owner_link.owner, 0x3a);
                display_scene_stage_0800ef2c(g_display_scene_byte2);
                audio_play_animation_cue(0);
            }
        } else if (g_input_pressed[g_input_config.local_player] & 0x10) {
            if (state->parameter <= 2) {
                ++state->parameter;
                g_display_scene_owner_link.owner->id = 0xb8 + state->parameter;
                frame_set_variant_state((void *)g_display_scene_owner_link.owner, 0x3a);
                display_scene_stage_0800ef2c(g_display_scene_byte2);
                audio_play_animation_cue(0);
            }
        } else if (g_input_pressed[g_input_config.local_player] & 0x40) {
            if (g_display_scene_byte2) {
                --g_display_scene_byte2;
                display_scene_stage_0800f034(g_display_scene_byte2);
                display_scene_stage_0800ef2c(g_display_scene_byte2);
                audio_play_animation_cue(0);
                display_scene_stage_0800f478();
            } else
                audio_play_animation_cue(3);
        } else if (g_input_pressed[g_input_config.local_player] & 0x80) {
            int page = g_display_scene_byte2;
            register unsigned char count asm("r1") = g_display_scene_byte0;
            register int limit asm("r0") = ((count + 3) >> 2) - 1;
            if (page < limit) {
                g_display_scene_byte2 = page + 1;
                display_scene_stage_0800f034(g_display_scene_byte2);
                display_scene_stage_0800ef2c(g_display_scene_byte2);
                audio_play_animation_cue(0);
                display_scene_stage_0800f478();
            } else
                audio_play_animation_cue(3);
        }
        break;
    }
    if (g_display_scene_request_state.unknown_10) {
        if ((g_input_pressed[g_input_config.local_player] & 2) && g_resource_scene_arg == 11) {
            display_scene_stage_08027dc0(11);
            audio_play_animation_cue(2);
        }
        if (g_input_pressed[g_input_config.local_player] & 0x100) goto change_selection_mode;
        if (g_input_pressed[g_input_config.local_player] & 0x200) goto change_selection_mode;
        if (advance != 1) return;
change_selection_mode:
        {
            if (g_display_scene_request_state.unknown_10 == 1) {
                g_display_scene_request_state.unknown_10 = 2;
                g_display_scene_owner_link.first_owner->flags &= ~1;
                g_display_scene_owner_link.owner->flags |= 1;
                g_display_scene_request_state.parameter = 0;
                g_display_scene_byte2 = 0;
                g_display_scene_byte1 = 0;
                g_display_scene_byte0 = 0;
                display_scene_stage_0800f034(0);
                display_scene_stage_0800f478();
                display_scene_stage_0800ef2c(0);
            } else {
                g_display_scene_request_state.unknown_10 = 1;
                g_display_scene_owner_link.first_owner->flags |= 1;
                g_display_scene_owner_link.owner->flags &= ~1;
            }
            audio_play_animation_cue(0);
        }
    }
}
