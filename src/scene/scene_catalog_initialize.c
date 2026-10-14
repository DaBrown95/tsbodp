#include "scene_catalog.h"
void scene_catalog_initialize(void) {
 unsigned int control,mode;
 unsigned int tile;
 display_set_mode(0);
 display_enable_layers(0x1000);
 display_show_background(3,g_scene_catalog_bg3);
 display_show_background(2,g_scene_catalog_bg2);
 control=g_scene_catalog_bg0;
 display_show_background(0,control);
 display_fill_background(0,0);
 display_text_set_background_control(control);
 if(g_scene_request.mode==0)g_scene_catalog_state.selector=g_scene_request.scene;
 g_scene_request.scene=0;
 g_scene_request.parameter=0;
 g_scene_request.unknown_10=0;
 g_scene_catalog_state.page_start=0;
 g_scene_catalog_state.row=0;
 g_scene_catalog_state.count=g_scene_catalog_world.catalog->count;
 g_scene_catalog_state.value=g_scene_catalog_world.entries[g_scene_catalog_state.selector].value;
 if(g_scene_catalog_world.clock.hour>=g_scene_catalog_start_hour.hour && g_scene_catalog_world.clock.hour<g_scene_catalog_end_hour.hour) {
  if(g_scene_catalog_state.selector==7 || g_scene_catalog_state.selector==9) {
   g_scene_request.mode=1;
   if(g_scene_previous_request.unknown_00!=23)g_scene_request.unknown_10=1;
  } else g_scene_request.mode=0;
 } else g_scene_request.mode=0;
 if(g_scene_catalog_state.selector==4) {
  g_scene_catalog_last_row=8;g_scene_catalog_first_row=0;g_scene_catalog_action_row=5;
 } else {
  g_scene_catalog_last_row=7;g_scene_catalog_first_row=0;g_scene_catalog_action_row=4;
 }
 display_load_resource_palette(&g_scene_catalog_palette,0);
 if(g_scene_catalog_state.selector==13)display_load_background(3,&g_scene_catalog_background3_alt,1,4,0,0);
 else display_load_background(3,&g_scene_catalog_background3,1,4,0,0);
 display_set_background_velocity(3,0x8000,0x8000);
 if(g_scene_catalog_state.selector==4) {
  display_load_background(2,&g_scene_catalog_background2_alt,181,1,0,0);
  display_show_background(1,g_scene_catalog_bg1_alt);
  display_fill_background(1,0);
 } else display_load_background(2,&g_scene_catalog_background2,181,1,0,0);
 display_load_palette(g_scene_catalog_text_palette,32,16);
 mode=g_scene_request.unknown_10;
 if(mode==1) {
  display_show_background(1,g_scene_catalog_bg1);
  display_load_background(1,&g_scene_catalog_background1,392,3,0,0);
  control=g_scene_catalog_bg0_alt;
  display_show_background(0,control);
  display_text_set_background_control(control);
  display_text_select_font(3,0,-1);
  display_text_draw_all_lines(131,120,16,200,display_scene_lookup_text(301),mode);
 } else {
  scene_catalog_prepare_original();
  mode=1;
  display_text_select_font(3,0,0);
  {const char *label=display_scene_lookup_text(0x181e);
  register unsigned int style asm("r4")=1;
  tile=display_text_draw_line(1,60,4,label,mode);
  display_text_draw_line(tile,188,4,display_scene_lookup_text(g_scene_catalog_state.selector+0x1820),style);}
  scene_catalog_fill_original(0,0);
  scene_catalog_draw_original(0,0);
  scene_catalog_build();
  scene_catalog_update();
 }
 transition_run_first(63,0);
}
asm(".align 2,0");
