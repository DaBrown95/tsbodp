#include "display_scene_lifecycle.h"
void display_scene_close(void)
{
    transition_run_second(0x3f, 0);
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_reset_palette_jobs();
    display_scene_clear_object_slots();
}
