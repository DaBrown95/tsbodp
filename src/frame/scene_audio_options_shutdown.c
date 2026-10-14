#include "scene_audio_options.h"
void scene_audio_options_shutdown(void) {
 transition_run_second(63,0);display_fill_background(0,0);
 display_release_object_list(&g_frame_primary_list);display_reset();display_reset_palette_jobs();display_scene_clear_object_slots();audio_game_clear_indexed_channels_alternate();
}
asm(".align 2,0");
