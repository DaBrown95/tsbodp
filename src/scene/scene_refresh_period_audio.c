#include "scene_environment.h"
void scene_refresh_period_audio(void)
{
 unsigned int period=display_time_period((const struct DisplayTimeRecord *)g_scene_world_state);
 if(g_scene_context.period!=period&&!(g_audio_control.flags&8)){
  unsigned char sequence=0;
  switch(period){
  case 0:sequence=g_scene_period_audio[g_scene_id].sequences[0];break;
  case 1:sequence=g_scene_period_audio[g_scene_id].sequences[1];break;
  case 2:sequence=g_scene_period_audio[g_scene_id].sequences[2];break;
  case 3:sequence=g_scene_period_audio[g_scene_id].sequences[3];break;
  }
  audio_select_sequence(sequence);
 }
}
