#include "scene_relation_grid.h"
void scene_relation_grid_shutdown(void)
{
 transition_run_second(63,0);
 display_release_object_list(&g_frame_primary_list);
 display_reset();
 display_reset_palette_jobs();
 display_scene_clear_object_slots();
}
asm(".align 2,0");
