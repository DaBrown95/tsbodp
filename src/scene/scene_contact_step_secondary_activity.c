#include "scene_contact_menu.h"

void scene_contact_step_secondary_activity(void)
{
    g_scene_contact_definitions[g_scene_contact_state->scene].step();
}
