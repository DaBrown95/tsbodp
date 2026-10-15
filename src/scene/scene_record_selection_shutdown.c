#include "scene_record_selection_handoffs.h"

void scene_record_selection_shutdown(void)
{
 transition_run_second(63, 12);
 audio_game_clear_indexed_channels_alternate();
 display_release_object_list(&g_frame_primary_list);
 display_reset();
 display_scene_clear_object_slots();
 heap_free((void *)g_frame_actor_palette_scene_resource);
}
