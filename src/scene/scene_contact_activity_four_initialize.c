#include "scene_contact_activity_four.h"

#define STATE ((struct SceneContactActivityFourState *)g_scene_contact_state)

void scene_contact_activity_four_initialize(void)
{
    display_show_background(1, g_scene_contact_activity_four_background1);
    display_show_background(2, g_scene_contact_activity_four_background2);
    display_show_background(3, g_scene_contact_initial_background_control1);
    display_load_background(1, &g_scene_contact_activity_four_map1, 390, 0, 0, 0);
    display_load_background(2, &g_scene_contact_activity_four_map2, 1, 0, 0, 0);
    display_load_background(3, &g_scene_contact_activity_four_map3, 780, 0, 0, 0);
    display_time_copy(&g_display_countdown,
        &g_scene_contact_activity_four_rows[g_scene_contact_state->option].clock);
    scene_contact_activity_four_reset_items();
    g_scene_request.unknown_14 =
        g_scene_contact_activity_four_rows[g_scene_contact_state->option].interval;
    scene_contact_activity_four_load_palettes();
    STATE->object = scene_contact_original_create_four_primary();
    STATE->control = scene_contact_original_create_four_control();
    scene_contact_original_create_four_auxiliary();
}
