#include "scene_primary.h"
void scene_primary_step(void)
{
 struct ScenePrimaryViews *context=&g_scene_primary_views;
 unsigned char selected=context->current_view;
 struct FrameActorObject *actor=context->slots[selected].object;
 if(!(g_scene_primary_view_flags[selected].flags&0x1c0000))scene_stage_0803c598();
 if(scene_step_early_exit()==1){g_game_flags&=~0x20u;return;}
 {
  unsigned char i=0;
  unsigned char first_count=context->count;
  unsigned char *variant=&actor->variant_state;
  if(i<first_count){unsigned char *count=&context->count;do {frame_update_map_view(i);scene_stage_0800e3a8(i);++i;}while(i<*count);}
  frame_step_transient_effects();scene_step_character_animation();
  if(*variant!=5 && (actor->state==16||actor->state==27)) {
   struct ResourceViewEffect *effects=g_resource_view_effects;
   unsigned char current=g_scene_primary_views.current_view;
   if(effects[current].mode!=1 && !(g_game_flags&0x810)) {
    if(g_input_pressed[current]&8){scene_submit_default_request(g_scene_primary_game_selection.requested_kind);audio_play_animation_cue(4);}
    else if((g_input_pressed[0]&4)||(g_input_pressed[1]&4)){scene_submit_default_request(11);audio_play_animation_cue(4);}
   }
  }
  for(i=0;i<g_scene_primary_views.count;i++){
   if((g_scene_primary_view_changes[i].changed&1)&&i==g_scene_primary_views.current_view){scene_refresh_period_audio();scene_refresh_environment();}
   if(!scene_request_changed())scene_update_view(i);
  }
 }
}
