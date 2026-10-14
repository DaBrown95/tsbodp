#include "scene_default_menu.h"

void scene_default_menu_shutdown(void)
{
    transition_fade_black_out_refresh_twice(63);
    display_release_object_list(&g_frame_primary_list);
    if (scene_queued_request_kind() != 6)
        display_reset();
    display_reset_palette_jobs();
    display_scene_clear_object_slots();
    audio_game_clear_indexed_channels_alternate();
}
