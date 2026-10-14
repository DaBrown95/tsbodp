#include "scene_link_menu.h"

void scene_link_menu_shutdown(void)
{
    g_scene_request.parameter = -1;
    transition_run_second(63, 12);
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_reset_palette_jobs();
    display_scene_clear_object_slots();
    audio_game_clear_indexed_channels_alternate();
    if (scene_queued_request_kind() == 5)
        scene_clear_retained_display();
}
