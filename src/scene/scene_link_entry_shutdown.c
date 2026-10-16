#include "scene_link_entry_setup.h"
#include "scene_request_queue.h"

void scene_link_entry_shutdown(void)
{
    if (!(g_game_flags & 0x20))
        transition_run_second(63, 0);
    else
        transition_fade_black_out_record(63);
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_reset_palette_jobs();
    display_scene_clear_object_slots();
}
