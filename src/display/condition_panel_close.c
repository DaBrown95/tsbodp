#include "display_condition_panel_lifecycle.h"

void condition_panel_close(void)
{
    g_display_scene_request_state.parameter = -1;
    transition_run_second(63, 0);
    display_release_object_list(&g_frame_primary_list);
    display_reset();
    display_scene_stage_080117bc();
    display_scene_clear_object_slots();
}
