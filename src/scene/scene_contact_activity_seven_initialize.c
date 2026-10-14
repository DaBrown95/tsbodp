#include "scene_contact_activity_seven.h"
void scene_contact_activity_seven_initialize(void) {
 display_show_background(3,g_scene_contact_initial_background_control1);
 display_show_background(2,g_scene_contact_activity_four_background2);
 display_show_background(1,g_scene_contact_activity_four_background1);
 display_load_background(3,&g_scene_contact_activity_seven_background3,1,0,0,0);
 display_load_background(2,&g_scene_contact_activity_seven_background2,183,0,0,0);
 display_load_background(1,&g_scene_contact_activity_seven_background1,0,0,0,0);
 frame_define_palette_slot(2,g_scene_contact_activity_seven_palette2);
 frame_define_palette_slot(3,g_scene_contact_activity_seven_palette3);
 STATE->primary=scene_contact_activity_seven_create_primary();
 STATE->status=scene_contact_activity_seven_create_status();
 scene_contact_activity_seven_draw_status();
}
