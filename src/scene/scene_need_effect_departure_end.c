#include "frame_need_effect_departure.h"

void scene_need_effect_departure_end(void)
{
    transition_run_second(63, 0);
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_reset_palette_jobs();
}
