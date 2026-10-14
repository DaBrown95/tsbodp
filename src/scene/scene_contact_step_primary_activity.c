#include "scene_contact_menu.h"

void scene_contact_step_primary_activity(void)
{
    SceneContactActivityCallback step;

    frame_update_map_view(0);
    transition_step_view(0);
    frame_step_transient_effects();
    step = g_scene_contact_definitions[g_scene_contact_state->scene].step;
    if (step)
        step();
}
