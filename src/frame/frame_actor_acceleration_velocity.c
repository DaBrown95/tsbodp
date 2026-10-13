#include "frame_actor_needs.h"
#include "input.h"
#include "view_math.h"
#include "audio_game.h"
#include "frame_actor_speed.h"
void frame_actor_acceleration_velocity(struct FrameObject *object,struct FramePoint *velocity)
{
 if(((struct FrameActorSpeedProbe *)object)->blocked==0) {
  if(g_input_current[g_frame_actor_need_input.local_player]&1) {
   if(g_frame_actor_controlled_speed==0&&g_frame_actor_speed_cue_mode!=1)frame_actor_play_speed_cue(74,1);
   g_frame_actor_controlled_speed+=0x3333;
   if(g_frame_actor_controlled_speed>0x80000) {
    g_frame_actor_controlled_speed=0x80000;
    frame_adjust_actor_needs(((struct FrameActorObject *)object)->actor_state,34,1);
   }
   if(g_frame_actor_controlled_speed>0x40000&&g_frame_actor_speed_cue_mode!=2)frame_actor_play_speed_cue(75,2);
  } else {
   if(g_frame_actor_controlled_speed==0x80000) {
    if(g_frame_actor_speed_cue_mode!=3||!audio_game_sample_active(g_frame_actor_speed_cue_handle))frame_actor_play_speed_cue(76,3);
   }
   if(g_frame_actor_controlled_speed>0x6665)g_frame_actor_controlled_speed-=0x6666;
   else {
    g_frame_actor_controlled_speed=0;
    if(g_frame_actor_speed_cue_mode!=4) {audio_game_stop_sample(g_frame_actor_speed_cue_handle);g_frame_actor_speed_cue_mode=4;}
   }
  }
 } else {
  audio_game_stop_sample(g_frame_actor_speed_cue_handle);
  g_frame_actor_speed_cue_mode=4;
  g_frame_actor_controlled_speed=0;
 }
 frame_make_velocity(velocity,object->flags,((struct FrameActorObject *)object)->direction,g_frame_actor_controlled_speed);
 frame_request_animation((struct FrameCommandObject *)object,86);
}
