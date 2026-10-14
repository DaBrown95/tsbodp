#include "scene_map_selection.h"
#include "display_motion.h"
#include "save_stream.h"
#include "resource_conditions.h"
#include "frame_scene_motion.h"
#include "display_palette_lifecycle.h"

void scene_map_selection_shutdown(void)
{
    transition_run_second(63, 0);
    display_reset_palette_jobs();
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_scene_clear_object_slots();
}

asm(".align 2, 0");
