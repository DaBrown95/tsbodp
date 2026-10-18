#include "scene_row24_selection_private.h"

void scene_row24_selection_step(void)
{
    if (g_input_pressed[g_input_config.local_player] & 0xf0) {
        unsigned char previous = (unsigned char)g_scene_request.scene;

        if (g_input_local_pressed[g_input_config.local_player] & 0x80)
            g_scene_request.scene = scene_row24_selection_move(1);
        else if (g_input_local_pressed[g_input_config.local_player] & 0x40)
            g_scene_request.scene = scene_row24_selection_move(0);

        if (g_input_local_pressed[g_input_config.local_player] & 0x20)
            g_scene_request.scene = scene_row24_selection_move(2);
        else if (g_input_local_pressed[g_input_config.local_player] & 0x10)
            g_scene_request.scene = scene_row24_selection_move(3);

        if (previous != g_scene_request.scene) {
            audio_play_animation_cue(0);
            scene_row24_selection_refresh_original();
        }
    }
    if (g_input_pressed[g_input_config.local_player] & 2) {
        scene_submit_default_request(11);
        audio_play_animation_cue(2);
    }
}
