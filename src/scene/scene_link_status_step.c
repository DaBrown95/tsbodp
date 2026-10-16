#include "scene_link_status_private.h"
void scene_link_status_step(void)
{
 unsigned int status=1;
 int index;
 struct EventPayload payload;
 if(g_link_flags&32768){
  resource_submit_scene(1,2,g_scene_id);
  {
   /* The character view starts at this same complete object. */
   unsigned char *config_bytes=(unsigned char *)&g_input_config;
   config_bytes[48]=status;
  }
  g_input_config.local_player=0;
  return;
 }
 switch(g_scene_request.unknown_10){
 case 3:{
  unsigned int start_result=link_start_status_poll(4);
  if(start_result!=7 && start_result!=5)g_scene_request.unknown_10=4;
  if(g_input_pressed[g_link_byte_03007340]&2){
   scene_stage_0803e3a8();
   resource_submit_scene(1,2,g_scene_id);
  }
  scene_link_status_draw_notice(0);
  break;
 }
 case 4:
  if(!(g_frame_flags&32))status=link_read_status_original();
  if(status-2<=2)g_scene_request.unknown_10=0;
  if(g_input_pressed[g_link_byte_03007340]&2){
   scene_stage_0803e3a8();
   resource_submit_scene(1,2,g_scene_id);
  }
  if(++g_link_status_flicker>15)g_link_status_visible_count=0;
  else g_link_status_visible_count=link_read_endpoint_active();
  for(index=0;index<g_link_status_visible_count;index++)g_link_status_indicators[index]->flags|=1;
  for(;index<4;index++)g_link_status_indicators[index]->flags&=~1u;
  break;
 case 0:
  status=1;
  if(!(g_frame_flags&32))status=link_read_status_original();
  if((unsigned char)link_peer_responses_complete() && status!=0 && status!=6){
   scene_link_status_draw_notice(event_get_link_slot()==0?1:2);
   if(!(g_save_stream_state.header.words[6]&2)){
    g_save_stream_state.header.words[6]|=2;
    save_stream_commit_header();
    audio_play_sequence_notification(63);
    display_text_select_font(3,0,0);
    display_text_draw_line(177,120,110,display_scene_lookup_text(240),1);
   }
   if(event_get_link_slot()==0 && (g_input_pressed[0]&1))link_wait_for_status_confirmation();
  if(++g_link_status_flicker>15)g_link_status_visible_count=0;
  else g_link_status_visible_count=link_read_endpoint_active();
  for(index=0;index<g_link_status_visible_count;index++)g_link_status_indicators[index]->flags|=1;
  for(;index<4;index++)g_link_status_indicators[index]->flags&=~1u;
   g_link_status_previous_count=g_link_status_visible_count;
  }
  if((g_link_flags&4) && (g_frame_flags&32)){
   g_scene_request.unknown_10=2;
   break;
  }
  if(status==1)g_scene_request.unknown_10=4;
  if(++g_link_status_flicker>15)g_link_status_visible_count=0;
  else g_link_status_visible_count=link_read_endpoint_active();
  for(index=0;index<g_link_status_visible_count;index++)g_link_status_indicators[index]->flags|=1;
  for(;index<4;index++)g_link_status_indicators[index]->flags&=~1u;
  if(g_input_pressed[g_link_byte_03007340]&2){
   scene_stage_0803e3a8();
   resource_submit_scene(1,2,g_scene_id);
  }
  break;
 case 2:
  g_scene_request.unknown_10=1;
  break;
 case 1:
  if(g_link_flags&4){
   struct FrameObject **slot;
   int remaining;
   unsigned int preserve_flags;
   register unsigned int set_flags asm("r3");
   transition_fade_black_out_record(63);
   display_clear_background_map(0);
   display_show_background(2,g_link_status_control2);
   display_load_background(2,&g_link_status_complete_background,0,1,0,0);
   display_text_select_font(3,0,-1);
   display_text_draw_all_lines(517,120,16,200,display_scene_lookup_text(302),1);
   g_link_status_visible_count=link_read_endpoint_active();
   preserve_flags=~17u;
   set_flags=2u;
   slot=g_link_status_indicators;
   for(remaining=3;remaining>=0;remaining--,slot++)(*slot)->flags=((*slot)->flags&preserve_flags)|set_flags;
   g_scene_request.unknown_10=6;
   g_input_config.player_count=g_link_peer_count;
   g_input_config.local_player=event_get_link_slot();
   g_scene_request.scene=0;
   scene_link_status_draw_notice(event_get_link_slot()==0?1:2);
   transition_fade_black_in_record(63);
  }
  break;
 case 5:
  g_link_received_join.identifier=-1;
  resource_submit_scene(16,2,0);
  g_input_config.player_count=g_link_peer_count;
  g_input_config.local_player=event_get_link_slot();
  break;
 case 6:
  if(g_input_pressed[0]&1)g_scene_request.unknown_10=5;
  else if(g_input_pressed[g_link_byte_03007340]&2){
   payload.storage.no_payload=(struct EventNoPayload){};
   transition_record_event(11,payload);
  }
  break;
 }
}
asm(".align 2,0");

#ifndef __clang__
typedef char empty_size[(sizeof(struct EventNoPayload)==0)?1:-1];
typedef char empty_align[(__alignof__(struct EventNoPayload)==4)?1:-1];
typedef char storage_size[(sizeof(union EventPayloadStorage)==8)?1:-1];
typedef char storage_align[(__alignof__(union EventPayloadStorage)==4)?1:-1];
typedef char payload_size[(sizeof(struct EventPayload)==8)?1:-1];
typedef char payload_align[(__alignof__(struct EventPayload)==4)?1:-1];
typedef char storage_offset[((unsigned int)&((struct EventPayload*)0)->storage==0)?1:-1];
typedef char bytes_offset[((unsigned int)&((struct EventPayload*)0)->storage.bytes==0)?1:-1];
typedef char none_offset[((unsigned int)&((struct EventPayload*)0)->storage.no_payload==0)?1:-1];
typedef char bytes_capacity[(sizeof(((struct EventPayload*)0)->storage.bytes)==8)?1:-1];
typedef char record_size[(sizeof(struct EventRecord)==12 && __alignof__(struct EventRecord)==4)?1:-1];
#endif
