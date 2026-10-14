#include "scene_contact_menu.h"

void scene_contact_initialize_secondary_activity(void)
{
    unsigned int control = g_scene_contact_background_control;

    display_show_background(0, control);
    display_fill_background(0, 0);
    display_text_set_background_control(control);
    g_scene_contact_definitions[g_scene_contact_state->scene].initialize();
    display_load_resource_palette(&g_scene_contact_palette_resource, 0);
}
