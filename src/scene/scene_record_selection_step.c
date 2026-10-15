#include "scene_record_selection.h"
void scene_record_selection_step(void)
{
 unsigned int index, old_choice;
 unsigned char player;
 switch(g_scene_request.unknown_10) {
 case 0:
  if(--g_scene_request.unknown_14==~0U) {
   g_condition_panel_objects[4]->flags|=1;
   g_condition_panel_objects[5]->flags|=1;
   g_scene_request.unknown_10=SCENE_RECORD_SELECTION_STATE->return_phase;
  }
  break;
 case 1: {
  if(g_input_local_pressed[g_frame_actor_need_input.local_player]&0x30)scene_record_selection_change_slot();
  else if(g_input_local_pressed[g_frame_actor_need_input.local_player]&1)scene_record_selection_confirm();
  else if(g_input_local_pressed[g_frame_actor_need_input.local_player]&2)scene_record_selection_cancel();
  break;
 }
 case 2:
  if(--g_scene_request.unknown_14==~0U)
   g_scene_request.unknown_10=SCENE_RECORD_SELECTION_STATE->return_phase;
  break;
 case 3:
  for(index=0;index<1;++index)display_scene_retire_object_slot(index);
  if(SCENE_RECORD_SELECTION_STATE->unknown_0c[1])frame_create_palette_scene_actor(2);
  else frame_create_palette_scene_actor(1);
  scene_record_selection_draw_panel_original();
  scene_record_selection_set_phase_original(SCENE_RECORD_SELECTION_STATE->unknown_0c[1]==0,1);
  break;
 case 4:
  display_text_set_background_control(g_scene_record_selection_control0);
  display_text_select_font(3,0,0);
  display_text_draw_line(147,120,36,display_scene_lookup_text(252),1);
  scene_record_selection_draw_choice(0,g_scene_request.scene);
  scene_record_selection_draw_choice(1,g_scene_request.scene);
  display_load_palette_ranges(&g_scene_default_menu_palette_ranges);
  g_scene_request.unknown_10=5;
  break;
 case 5: {
  if(g_input_local_pressed[player=g_frame_actor_need_input.local_player]&0xc0) {
   old_choice=g_scene_request.scene;
   input_step_local_vertical_pressed(&g_scene_request.scene,0,1,1,player);
   scene_record_selection_draw_choice(old_choice,g_scene_request.scene);
   scene_record_selection_draw_choice(g_scene_request.scene,g_scene_request.scene);
   audio_play_animation_cue(0);
   break;
  }
  if((g_input_local_pressed[player]&1)&&g_scene_request.scene==0) {
   g_scene_request.unknown_10=6;
   audio_play_animation_cue(1);
   break;
  }
  if((g_input_local_pressed[g_frame_actor_need_input.local_player]&2)||
     ((g_input_local_pressed[g_frame_actor_need_input.local_player]&1)&&g_scene_request.scene==1)) {
   display_fill_background(0,0);
   display_reset_palette_jobs();
   scene_record_selection_set_phase_original(SCENE_RECORD_SELECTION_STATE->unknown_0c[1],1);
   audio_play_animation_cue(2);
  }
  break;
 }
 case 6:
  display_text_set_background_control(g_scene_record_selection_control0);
  display_fill_background(0,0);
  display_text_select_font(3,0,0);
  display_text_draw_line(147,120,36,display_scene_lookup_text(256),1);
  g_scene_request.unknown_10=7;
  break;
 case 7:
  save_stream_commit_header();
  save_stream_commit_slot(g_scene_request.parameter);
  display_fill_background(0,0);
  display_text_select_font(3,0,0);
  display_text_draw_line(147,120,36,display_scene_lookup_text(254),1);
  g_scene_request.unknown_10=8;
  g_scene_request.unknown_14=20;
  break;
 case 8:
  if(--g_scene_request.unknown_14==~0U)scene_submit_default_request(11);
  break;
 }
}
