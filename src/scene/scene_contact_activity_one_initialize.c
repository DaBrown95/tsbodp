#include "scene_contact_activity_one.h"
#define STATE ((struct SceneContactActivityOneState*)g_scene_contact_state)
void scene_contact_activity_one_initialize(void) {
 display_show_background(3,g_scene_contact_activity_one_background_control);
 display_fill_background(3,0);
 display_load_background(3,&g_scene_contact_activity_one_background,43,1,0,0);
 frame_define_palette_slot(1,g_scene_contact_activity_one_palette1);
 frame_define_palette_slot(2,g_scene_contact_activity_one_palette2);
 STATE->primary=scene_contact_activity_one_create_primary();
 STATE->secondary=scene_contact_activity_one_create_secondary();
 g_scene_request.unknown_10=0;STATE->flags|=2;
}
asm(".align 2,0");
