#include "scene_contact_menu.h"
void scene_contact_shutdown(void)
{
    transition_run_second(63, 0);
    if (!(g_scene_contact_state->flags & 16)) {
        if (g_scene_contact_state->scene <= 1)
            frame_clear_scene_effects();
        else
            scene_contact_clear_activity_objects();
        heap_free(g_scene_contact_state);
    } else
        g_scene_contact_state->flags &= ~16;
    audio_game_clear_indexed_channels_alternate();
    display_reset_palette_jobs();
    display_reset();
    frame_release_map_resources();
    set_vblank_callback(irq_default_vblank_callback);
}
