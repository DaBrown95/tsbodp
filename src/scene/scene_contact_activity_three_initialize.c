#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
void scene_contact_activity_three_initialize(void) {
 unsigned int i;
 display_show_background(3,g_scene_contact_initial_background_control1);
 display_show_background(2,g_scene_contact_activity_four_background2);
 display_show_background(1,g_scene_contact_activity_four_background1);
 display_fill_background(1,0);
 display_load_background(3,&g_scene_contact_activity_three_background3,1,0,(i=0),0);
 display_load_background(2,&g_scene_contact_activity_three_background2,570,0,i,i);
 display_load_palette_ranges(&g_scene_contact_activity_three_palette_ranges);
 display_load_palette_alternate(g_scene_contact_activity_three_palette15[0],240,16);
 display_load_palette_alternate(g_scene_contact_activity_three_palette14[0],224,16);
 STATE->primary=scene_contact_activity_three_create_primary();
 STATE->secondary=scene_contact_activity_three_create_secondary();
 STATE->observer.object=scene_contact_activity_three_create_observer();
 STATE->cursor=scene_contact_activity_three_create_cursor();
 scene_contact_activity_three_clear_slots();
 g_scene_contact_activity_three_control.phase=i;
 g_scene_contact_activity_three_control.refresh_count=i;
 g_scene_contact_activity_three_control.selection.word=i;
 STATE->values[0]=g_scene_contact_activity_three_options[STATE->option].values[0];
 STATE->values[1]=g_scene_contact_activity_three_options[STATE->option].values[1];
 STATE->values[2]=g_scene_contact_activity_three_options[STATE->option].values[2];
 for(;i<=4;++i)scene_contact_activity_three_create_row(i);
 for(i=0;i<=2;++i) {
  scene_contact_activity_three_refresh_value((unsigned char)i,g_scene_contact_activity_three_control.selection.bytes[0]);
  {
   unsigned int row=i;
   row<<=1;
   display_load_background(1,g_scene_contact_activity_three_background_entries[i].background,(unsigned short)(31+i*4),(unsigned short)(10-i),1,row+14);
  }
 }
}
asm(".align 2,0");
