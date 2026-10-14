#include "scene_palette_menu_input.h"
void scene_palette_menu_phase_1(void)
{
    register unsigned int pressed asm("r1") = g_input_local_pressed[g_input_config.local_player];
    if (pressed & 1) {
        if (g_scene_request.scene == 3) {
            if (g_frame_actor_palette_menu_exit_count) {
                unsigned char i;
                heap_clear(g_frame_actor_palette_menu_state.text, 0, 16);
                for (i = 0; i < g_frame_actor_palette_menu_exit_count; ++i)
                    display_append_text_resource((char *)g_frame_actor_palette_menu_state.text,
                        g_frame_actor_palette_menu_exit_objects[i]->unknown_0a);
                g_scene_request.unknown_10 = 2;
                g_scene_request.unknown_14 = 30;
                {
                    unsigned int next = g_scene_request.mode;
                    if (next != 7)
                        next = 6;
                    g_scene_request.parameter = next;
                }
                audio_play_animation_cue(12);
            } else {
                audio_play_animation_cue(3);
            }
        } else {
            const char *text;
            if (g_frame_actor_palette_menu_exit_count > 7)
                return;
            text = display_scene_lookup_text(g_palette_menu_character_ids
                [g_frame_actor_palette_menu_text_flag][g_scene_request.scene]
                [g_scene_request.parameter]);
            display_text_select_font(1, 0, 0);
            g_frame_actor_palette_menu_exit_objects[g_frame_actor_palette_menu_exit_count] =
                display_allocate_text_object(&text);
            if (g_frame_actor_palette_menu_exit_count == 0) {
                frame_set_position(g_frame_actor_palette_menu_exit_objects
                    [g_frame_actor_palette_menu_exit_count],
                    (g_frame_actor_palette_menu_exit_count * 9 + 67) * 65536, 37 * 65536);
            } else {
                struct FrameObject *previous = g_frame_actor_palette_menu_exit_objects
                    [g_frame_actor_palette_menu_exit_count - 1];
                if (previous->unknown_0a == 93 || previous->unknown_0a == 96)
                    frame_set_position(g_frame_actor_palette_menu_exit_objects
                        [g_frame_actor_palette_menu_exit_count],
                        previous->position.x + 4 * 65536, 37 * 65536);
                else
                    frame_set_position(g_frame_actor_palette_menu_exit_objects
                        [g_frame_actor_palette_menu_exit_count],
                        previous->position.x + 9 * 65536, 37 * 65536);
            }
            g_frame_actor_palette_menu_exit_objects[g_frame_actor_palette_menu_exit_count]->unknown_0a =
                g_palette_menu_character_ids[g_frame_actor_palette_menu_text_flag]
                [g_scene_request.scene][g_scene_request.parameter];
            ++g_frame_actor_palette_menu_exit_count;
            audio_play_animation_cue(1);
        }
    } else if (pressed & 2) {
        if (g_frame_actor_palette_menu_exit_count) {
            --g_frame_actor_palette_menu_exit_count;
            if (g_frame_actor_palette_menu_exit_objects[g_frame_actor_palette_menu_exit_count]) {
                g_frame_actor_palette_menu_exit_objects[g_frame_actor_palette_menu_exit_count]->flags &= ~1U;
                g_frame_actor_palette_menu_exit_objects[g_frame_actor_palette_menu_exit_count]->flags |= 2;
            }
            audio_play_animation_cue(2);
        } else {
            g_scene_request.unknown_10 = 2;
            g_scene_request.unknown_14 = 30;
            g_scene_request.parameter = 13;
            audio_play_animation_cue(12);
        }
    } else if (pressed & 256) {
        g_frame_actor_palette_menu_text_flag = !g_frame_actor_palette_menu_text_flag;
        scene_palette_menu_refresh_character_bank();
        audio_play_animation_cue(1);
    } else if (pressed & 512) {
        g_frame_actor_palette_menu_text_flag = !g_frame_actor_palette_menu_text_flag;
        scene_palette_menu_refresh_character_bank();
        audio_play_animation_cue(1);
    } else if ((unsigned short)(pressed & 64)) {
        if (g_scene_request.scene)
            --g_scene_request.scene;
        else
            g_scene_request.scene = 3;
        if (g_scene_request.scene == 2) {
            if (!g_scene_request.parameter)
                g_scene_request.parameter = g_palette_menu_entry_ranges[2].first;
            else if (g_scene_request.parameter > g_palette_menu_entry_ranges[2].last)
                g_scene_request.parameter = g_palette_menu_entry_ranges[2].last;
        }
        scene_palette_menu_refresh_cursor();
    } else if (pressed & 128) {
        if (g_scene_request.scene < 3)
            ++g_scene_request.scene;
        else
            g_scene_request.scene = 0;
        if (g_scene_request.scene == 2) {
            if (!g_scene_request.parameter)
                g_scene_request.parameter = g_palette_menu_entry_ranges[2].first;
            else if (g_scene_request.parameter > g_palette_menu_entry_ranges[2].last)
                g_scene_request.parameter = g_palette_menu_entry_ranges[2].last;
        }
        scene_palette_menu_refresh_cursor();
    } else if (pressed & 32) {
        if (g_scene_request.scene != 3) {
            if (g_scene_request.parameter > g_palette_menu_entry_ranges[g_scene_request.scene].first)
                --g_scene_request.parameter;
            else
                g_scene_request.parameter = g_palette_menu_entry_ranges[g_scene_request.scene].last;
            scene_palette_menu_refresh_cursor();
        }
    } else if (pressed & 16) {
        if (g_scene_request.scene != 3) {
            if (g_scene_request.parameter < g_palette_menu_entry_ranges[g_scene_request.scene].last)
                ++g_scene_request.parameter;
            else
                g_scene_request.parameter = g_palette_menu_entry_ranges[g_scene_request.scene].first;
            scene_palette_menu_refresh_cursor();
        }
    }
}
asm(".align 2,0");
