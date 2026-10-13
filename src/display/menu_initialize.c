#include "display_menu_scene.h"
#include "display_scene_setup.h"
#include "display_catalog_text.h"
#include "display_catalog_presentation.h"
#include "display_window.h"
#include "frame_actor_relation.h"
#include "audio_game.h"
void display_menu_initialize(void) {
 unsigned int i,control;
 display_menu_clear_effects();
 { struct DisplayMenuState *menu=(struct DisplayMenuState *)&g_display_menu_state;
 menu->unknown_28=0;
 display_set_mode(0);
 display_enable_layers(0x1000);
 display_show_background(3,g_display_menu_control3);
 display_show_background(2,g_display_menu_control2);
 display_fill_background(2,0);
 display_show_background(1,g_display_menu_control1);
 display_fill_background(1,0x23c);
 control=g_display_menu_control0;
 display_show_background(0,control);
 display_fill_background(0,60);
 display_text_set_background_control(control);
 menu->resource_shown=0;
 menu->unknown_29=255;
 menu->unknown_2a=-1;
 menu->unknown_2b=-1;
 if(g_display_scene_request_state.mode!=1) {
  unsigned int definition=g_display_scene_request_state.scene;
  menu->definition=definition;
  g_display_scene_request_state.scene=0;
  g_display_scene_request_state.unknown_10=0;
  if(!((struct FrameActorRelationState *)&g_display_catalog_state)->records[definition].unknown_02[0])audio_play_animation_cue(g_frame_actor_greetings[definition].cue_record[7]);
  else {
   g_display_scene_request_state.mode=2;
   audio_play_animation_cue(g_frame_actor_greetings[definition].cue_record[0]);
  }
 }else if(!g_display_scene_request_state.scene)g_display_scene_request_state.mode=0;
 }
 i=0;
 { struct DisplayMenuState *menu=(struct DisplayMenuState *)&g_display_menu_state;
 for(;i<=4;++i)g_display_menu_state.codes[i]=29;
 menu->unknown_26=255;
 menu->unknown_27=-1;
 menu->choice=-1;
 { unsigned char *catalog=(unsigned char *)&g_display_catalog_state+0x10;
 display_menu_prepare_relation(catalog,menu->definition);
 catalog+=0x20;
 *catalog=display_menu_read_relation(catalog,menu->definition); }
 display_load_palette_alternate(g_display_menu_palette_data,0,16);
 if(g_display_scene_request_state.mode!=1) {
  display_load_background(2,g_frame_actor_greetings[menu->definition].background_resource,1,0,15,0);
  menu->resource_shown=1;
 }else display_load_resource_palette(g_frame_actor_greetings[menu->definition].background_resource,0);
 display_load_resource_palette(&g_display_menu_palette_resource,0);
 display_load_palette_ranges(&g_display_menu_palette_ranges);
 display_menu_load_relation_resource();
 /* One signed fixed-point pixel step on each background axis. */
 display_set_background_velocity(3,-65536,-65536);
 }
 { const unsigned short *map=display_load_background(1,&g_display_menu_panel_resource,278,13,0,0);
 struct DisplayMenuState *menu=(struct DisplayMenuState *)&g_display_menu_state;
 menu->unknown_0c[1]=(unsigned int)map;
 scene_view_load_selected_resource(1,1,15,426,15,
  (const struct SceneViewResourceSelection *)((const unsigned char *)&g_display_catalog_state+0x20));
 display_text_set_background_control(g_display_menu_control1);
 display_text_select_font(3,0,-1);
 display_text_set_line_height(12);
 display_text_draw_line(218,60,4,display_scene_lookup_text(menu->definition+0x1789),1);
 display_text_set_background_control(g_display_menu_control0);
 display_menu_prepare_footer();
 display_configure_window(0,0x3f,0x3e);
 display_set_window_rectangle(0,72<<16,116<<16,216<<16,152<<16);
 display_configure_window(1,0x3f,0x3e);
 display_set_window_rectangle(1,16<<16,32<<16,120<<16,92<<16);
 if(g_display_scene_request_state.mode==0) {
  display_menu_prepare_primary();
  display_disable_window(1);
 }else if(g_display_scene_request_state.mode==1) {
  display_menu_prepare_secondary();
  display_disable_window(0);
 }else if(g_display_scene_request_state.mode==2) {
  display_menu_prepare_tertiary();
  display_disable_window(0);
 }
 }
 g_display_scene_request_state.scene=0;
 transition_run_first(63,0);
}
asm(".align 2, 0");
