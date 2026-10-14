#include "scene_default_menu.h"

void scene_default_menu_accept(void)
{
    if (audio_game_sample_active(g_scene_default_menu_cue_handle))
        audio_game_stop_sample(g_scene_default_menu_cue_handle);
    switch (g_scene_request.scene) {
    case 0:
        scene_submit_default_request(19);
        break;
    case 1:
        g_scene_link_menu_selector_word = 5;
        resource_submit_scene(7, 0, 0);
        break;
    case 2:
        resource_submit_scene(6, 0, g_scene_request.unknown_00);
        break;
    case 3:
        scene_submit_default_request(10);
        break;
    }
    g_scene_default_menu_cue_handle = audio_play_animation_cue(1);
    frame_refresh_random_seed();
}
