#include "scene_contact_menu.h"

void scene_contact_initialize_primary_activity(void)
{
    unsigned int control;

    set_vblank_callback(scene_vblank_callback);
    control = g_scene_contact_background_control;
    display_show_background(0, control);
    display_show_background(1, g_scene_contact_activity_background_control1);
    display_show_background(2, g_scene_contact_initial_background_control1);
    scene_contact_load_primary_resources(g_scene_contact_state->scene);
    display_load_resource_palette(&g_scene_contact_palette_resource, 0);
    display_fill_background(0, 0);
    display_text_set_background_control(control);
    g_scene_contact_definitions[g_scene_contact_state->scene].initialize();
    transition_reset_view(0);
    transition_set_view_interpolation(0, 0);
    transition_set_view_mode(0, 0);
    transition_configure_view(
        ((struct SceneContactActivityStatePrefix *)g_scene_contact_state)->view,
        g_transition_view_configuration.point, 0);
    frame_update_map_view(0);
    transition_step_view(0);
}
