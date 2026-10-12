#include "frame_actor_scene.h"
#include "audio_game.h"
#include "display_catalog_text.h"
#include "frame_actor_actions.h"
void frame_advance_parameter_level(void *record,unsigned int index)
{
 int *value=(int *)record+index;
 unsigned int previous=(unsigned int)*value>>24;
 if(previous<=9) {
  *value+=0x1000000;
  if((*value>>24)>(int)previous) {
   unsigned char width,height;
   *value=(previous+1)<<24;
   condition_finish_actor_context(g_frame_parameter_refresh_context);
   g_actor_scene_result_id.id=0x123;
   width=display_text_measure_width(display_scene_lookup_text(g_actor_scene_result_id.id));
   height=display_text_measure_height(display_scene_lookup_text(g_actor_scene_result_id.id));
   ((struct FrameActorParameterNotification *)&g_actor_scene_request)->active=0;
   ((struct FrameActorParameterNotification *)&g_actor_scene_request)->x=(30-(width>>3))/2;
   ((struct FrameActorParameterNotification *)&g_actor_scene_request)->y=7-(height>>4);
   display_scene_stage_08027dc0(2);
   audio_play_sequence_notification(56);
  }
 }
}
