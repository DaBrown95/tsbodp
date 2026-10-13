#include "frame_actor_attachment_parameters.h"
void frame_update_attachment_parameter(void *record,unsigned int index,struct FrameObject *indicator)
{
 unsigned int *value=(unsigned int *)record+index;
 unsigned int initial=*value;
 unsigned int previous=initial>>24;
 if(previous<=9) {
  if(g_input_pressed[g_input_config.local_player]&1)*value=initial+(g_attachment_parameter_rates[index][previous]<<3);
  else *value=initial+g_attachment_parameter_rates[index][previous];
  { unsigned int address=(unsigned int)record;
  address+=index*4;
  if(*((signed char *)address+3)>(int)previous) {
   *(unsigned int *)address=(previous+1)<<24;
   condition_finish_actor_context(g_frame_parameter_refresh_context);
   g_attachment_parameter_ui[g_input_config.local_player].flags|=0x40000;
   frame_complete_attachment_parameter_indicator(indicator);
   audio_play_sequence_notification(56);
  }
  }
 }
}
