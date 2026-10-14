#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_initialize(void)
{
 display_show_background(1,g_scene_contact_activity_four_background1);
 display_show_background(3,g_scene_contact_initial_background_control1);
 display_load_background(1,&g_scene_contact_activity_five_background1,1,0,0,0);
 display_load_background(3,&g_scene_contact_activity_five_background3,1,0,0,0);
 frame_reset_object_palette_slots();
 STATE->root=0;
 scene_contact_activity_five_reset();
 g_scene_request.unknown_10=0;
}
