#include "frame.h"
#include "input.h"
#include "scene_catalog.h"
void scene_catalog_step(void) {
 unsigned int phase=g_scene_request.unknown_10;
 register unsigned int keys asm("r1");
 unsigned int tile,control,confirm;
 switch(phase) {
 case 0:
  if(g_input_pressed[g_input_config.local_player]&0xf0) {
   keys=g_input_local_pressed[g_input_config.local_player];
   if(keys&0x80)scene_catalog_next();
   else if(keys&0x40)scene_catalog_previous();
   else if(keys&0x20) {
    if(g_scene_request.scene!=g_scene_catalog_first_row)g_scene_request.scene--;
   } else if(keys&0x10) {
    if(g_scene_request.scene!=g_scene_catalog_last_row)g_scene_request.scene++;
   }
   scene_catalog_selection();
   audio_play_animation_cue(0);
   scene_catalog_update();
  }
  keys=g_input_pressed[g_input_config.local_player];
  if(keys&1) {
   if(g_scene_request.scene>=g_scene_catalog_action_row)scene_catalog_confirm_original();
   else if(g_scene_catalog_state.selector==4)scene_catalog_begin_quantity();
   else if(g_scene_catalog_state.selector!=13)scene_catalog_option();
   if(g_scene_request.unknown_10!=2)scene_catalog_selection();
   break;
  }
  if(keys&2) {
   resource_submit_scene(1,2,g_frame_world_id);
   audio_play_animation_cue(2);
  }
  break;
 case 2:
  keys=g_input_local_pressed[g_input_config.local_player];
  if(keys&0x40) {
   if(g_scene_request.parameter<g_scene_catalog_world.quantities[g_scene_request.scene]) {
    g_scene_request.parameter++;
    audio_play_animation_cue(1);
   }
  } else if(keys&0x80) {
   if(g_scene_request.parameter>1) {
    g_scene_request.parameter--;
    audio_play_animation_cue(1);
   }
  }
  scene_catalog_quantity();
  keys=g_input_local_pressed[g_input_config.local_player];
  confirm=keys&1;
  if(confirm) {
   if(g_scene_catalog_world.quantities[g_scene_request.scene]>=g_scene_request.parameter)
    g_scene_catalog_world.quantities[g_scene_request.scene]-=g_scene_request.parameter;
   if(g_scene_request.scene==0 && g_scene_request.parameter!=0)resource_set_triple(1,4,3);
   frame_add_game_value(g_scene_request.parameter*g_scene_catalog_world.values[g_scene_request.scene]);
   g_scene_request.parameter=0;
   display_fill_background(1,0);
   g_scene_request.unknown_10=0;
   display_text_set_background_control(g_scene_catalog_bg0);
   g_display_scene_frame_objects[11]->flags&=~1U;
   g_display_scene_frame_objects[12]->flags&=~1U;
   scene_catalog_build();
   scene_catalog_refresh_quantities();
   audio_play_animation_cue(5);
  } else if(keys&2) {
   g_scene_request.parameter=confirm;
   display_fill_background(1,0);
   g_scene_request.unknown_10=confirm;
   display_text_set_background_control(g_scene_catalog_bg0);
   g_display_scene_frame_objects[11]->flags&=~1U;
   g_display_scene_frame_objects[12]->flags&=~1U;
   audio_play_animation_cue(2);
  }
  break;
 case 1:
  keys=g_input_local_pressed[g_input_config.local_player];
  if(keys&phase) {
   transition_run_second(63,0);
   control=g_scene_catalog_bg0;
   display_show_background(0,control);
   display_text_set_background_control(control);
   display_hide_background(1);
   display_fill_background(1,0);
   display_fill_background(0,0);
   g_scene_request.unknown_10=0;
   scene_catalog_prepare_original();
   display_text_select_font(3,0,0);
   tile=display_text_draw_line(1,60,4,display_scene_lookup_text(0x181e),phase);
   display_text_draw_line(tile,188,4,display_scene_lookup_text(g_scene_catalog_state.selector+0x1820),phase);
   scene_catalog_fill(0,0);
   scene_catalog_build();
   scene_catalog_update();
   transition_run_first(63,0);
  } else if(keys&2) {
   resource_submit_scene(1,2,g_frame_world_id);
   audio_play_animation_cue(2);
  }
  break;
 case 3:
  phase&=g_input_local_pressed[g_input_config.local_player];
  if(phase) {
   display_fill_background(1,0);
   g_scene_request.unknown_10=0;
  }
  break;
 }
}
asm(".align 2,0");
