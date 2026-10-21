#include "scene_phase25.h"
#include "scene_audio_options.h"
#include "display_scene_lifecycle.h"
#include "frame_actor_speed_control.h"

void scene_phase25_shutdown(void)
{
    transition_run_second(63, 0);
    audio_game_clear_indexed_channels();
    audio_game_set_sample_volume(g_audio_game_options.samples_volume);
    if (g_frame_actor_speed_effect)
        frame_destroy_transient_effect(g_frame_actor_speed_effect);
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_reset_palette_jobs();
    display_scene_clear_object_slots();
}
