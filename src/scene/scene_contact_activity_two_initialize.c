#include "scene_contact_activity_two.h"
#define STATE ((struct SceneContactActivityTwoState *)g_scene_contact_state)
void scene_contact_activity_two_initialize(void) {
 int i;
 display_show_background(3,g_scene_contact_initial_background_control1);
 display_show_background(2,g_scene_contact_activity_four_background2);
 display_show_background(1,g_scene_contact_activity_four_background1);
 display_fill_background(2,0);
 display_load_background(3,&g_scene_contact_activity_two_background3,1,0,0,0);
 display_load_background(1,&g_scene_contact_activity_two_background1,1,3,0,0);
 display_time_copy(&g_display_countdown,&g_scene_contact_activity_two_clock);
 for(i=6;i>=0;--i) {
  scene_contact_activity_two_draw_row(i);
  STATE->entries[i].object=scene_contact_activity_two_create_row(i);
 }
 display_load_palette_alternate(g_scene_contact_activity_two_event_resources[0].palette,g_scene_contact_activity_two_event_resources[0].palette_slot<<4,16);
 display_load_palette_alternate(g_scene_contact_activity_two_event_resources[1].palette,g_scene_contact_activity_two_event_resources[1].palette_slot<<4,16);
 display_load_palette_alternate(g_scene_contact_activity_two_event_resources[2].palette,g_scene_contact_activity_two_event_resources[2].palette_slot<<4,16);
 STATE->primary=scene_contact_activity_two_create_primary();
 STATE->secondary=scene_contact_activity_two_create_secondary();
 STATE->score=g_scene_contact_activity_two_scores[STATE->option].initial;
 scene_contact_activity_two_draw_score();
 STATE->event=scene_contact_activity_two_create_event(frame_random_range(0,2));
}
asm(".align 2, 0");
