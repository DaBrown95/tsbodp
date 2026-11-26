#include "scene_audio_options.h"
void scene_audio_options_change_level(void) {
 register struct SceneRequest *initial_request asm("r0")=&g_scene_request;unsigned int selector=initial_request->parameter;
 if(selector<=1){
  unsigned int value;unsigned char row;{register unsigned char *levels asm("r0")=g_scene_audio_option_levels;value=*(unsigned char *)(selector+(unsigned int)levels);}
  input_step_local_horizontal_pressed(&value,0,g_scene_audio_option_limits[selector],0,g_input_config.local_player);
  g_scene_audio_option_levels[g_scene_request.parameter]=value;
  switch(g_scene_request.parameter){
  case 0:
   if(value==10)value=255;else value*=25;
   if(!value&&g_audio_game_options.sequences_volume){audio_game_stop_sequence();audio_game_set_sequence_volume((unsigned char)value);}
   else if(value&&!g_audio_game_options.sequences_volume){
    unsigned char sequence;
    audio_game_set_sequence_volume((unsigned char)value);
    sequence=g_audio_control.sequence_id;g_audio_control.sequence_id=255;audio_select_sequence(sequence);
    break;
   }
   else audio_game_set_sequence_volume((unsigned char)value);
   break;
  case 1:
   if(value==10)value=128;else value*=12;
   if(!value&&g_audio_game_options.samples_volume)audio_game_clear_indexed_channels();
   audio_game_set_sample_volume((unsigned char)value);
   break;
  }
  for(row=0;row<=3;row++)scene_audio_options_draw_row(row);
  audio_game_stop_sample(g_scene_audio_option_cue);g_scene_audio_option_cue=audio_play_animation_cue(0);
 }
}
asm(".align 2,0");
