#include "display_menu_results.h"
#include "display_motion.h"
#include "frame_transient_effect.h"
#include "input.h"
#include "scene.h"
#include "scene_link_menu.h"

void display_menu_step(void)
{
    unsigned int phase;

    frame_step_transient_effects();
    phase = g_scene_request.unknown_10;
    if (phase == 0) {
        if (g_input_pressed[g_input_config.local_player] & 0xf0) {
            input_step_vertical_pressed(&g_scene_request.scene, 0, 4, 0,
                g_input_config.local_player);
            while (g_display_menu_state.codes[g_scene_request.scene] == 29)
                --g_scene_request.scene;
            if (g_scene_request.scene == 4 ||
                g_display_menu_state.codes[g_scene_request.scene + 1] == 29)
                g_display_scene_frame_objects[6]->flags &= ~1u;
            else
                g_display_scene_frame_objects[6]->flags |= 1;
            if (g_scene_request.scene == 0)
                g_display_scene_frame_objects[5]->flags &= ~1u;
            else
                g_display_scene_frame_objects[5]->flags |= 1;
            display_set_background_scroll_target(0, 0,
                (int)(((double)(int)g_display_menu_state.positions[g_scene_request.scene]
                    + -116.0) * 65536.0), 5);
            display_menu_draw_lines();
        }
        if (g_input_pressed[g_input_config.local_player] & 1) {
            g_display_scene_frame_objects[5]->flags &= ~1u;
            g_display_scene_frame_objects[6]->flags &= ~1u;
            g_display_scene_frame_objects[1]->flags &= ~1u;
            display_menu_execute_row();
        }
    } else if (phase == 1) {
        if (g_input_current[g_input_config.local_player] & 0xf0) {
            if (g_display_menu_state.repeat_delay == 0) {
                g_display_menu_state.repeat_delay = 4;
                input_step_vertical_held(&g_scene_request.scene, 0,
                    g_scene_request.parameter, 0, g_input_config.local_player);
                display_set_background_scroll_target(0, 0,
                    (g_scene_request.scene * 3) << 18, 5);
                if (g_scene_request.scene == 0 || g_scene_request.parameter == 0)
                    g_display_scene_frame_objects[3]->flags &= ~1u;
                else
                    g_display_scene_frame_objects[3]->flags |= 1;
                if (g_scene_request.scene == g_scene_request.parameter ||
                    g_scene_request.parameter == 0) {
                    g_display_scene_frame_objects[4]->flags &= ~1u;
                    g_display_scene_frame_objects[2]->flags |= 1;
                } else {
                    g_display_scene_frame_objects[4]->flags |= 1;
                    g_display_scene_frame_objects[2]->flags &= ~1u;
                }
            } else {
                --g_display_menu_state.repeat_delay;
            }
        } else {
            g_display_menu_state.repeat_delay = 0;
        }
        if ((g_input_pressed[g_input_config.local_player] & 1) &&
            (g_display_scene_frame_objects[2]->flags & 1)) {
            g_display_scene_frame_objects[3]->flags &= ~1u;
            g_display_scene_frame_objects[4]->flags &= ~1u;
            display_menu_prepare_primary();
        }
    } else if (phase == 2) {
        display_menu_step_result_effects();
        if (g_scene_request.unknown_14 == 0)
            display_menu_prepare_primary();
        else
            --g_scene_request.unknown_14;
    }
    if (g_input_pressed[g_input_config.local_player] & 2) {
        resource_submit_scene(1, 2, g_scene_id);
        audio_play_animation_cue(
            g_frame_actor_greetings[g_display_menu_state.definition].cue_record[8]);
    }
}
