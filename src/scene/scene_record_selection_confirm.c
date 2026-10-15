#include "scene_record_selection.h"
void scene_record_selection_confirm(void)
{
 switch(g_scene_request.mode) {
 case 0:
  if(SCENE_RECORD_SELECTION_STATE->occupied[g_scene_request.parameter]) {
   g_save_stream_state.selected=g_scene_request.parameter;
   save_stream_suspend_audio();
   save_stream_read_slot(g_save_stream_state.selected);
   save_stream_resume_audio();
   if((unsigned char)save_stream_validate_slot(g_save_stream_state.selected)) {
    resource_submit_scene(1,5,0);
    audio_play_animation_cue(1);
    break;
   }
  }
  audio_play_animation_cue(3);
  break;
 case 1:
  if(SCENE_RECORD_SELECTION_STATE->enabled[g_scene_request.parameter]) {
   if(SCENE_RECORD_SELECTION_STATE->occupied[g_scene_request.parameter])
    scene_record_selection_set_slot_phase_original(0,4);
   else scene_record_selection_set_slot_phase_original(0,6);
   g_scene_request.scene=1;
  } else audio_play_animation_cue(3);
  break;
 }
}
