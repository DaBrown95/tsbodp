#include "audio_game.h"
#include "frame_actor_speed.h"
void frame_actor_set_speed_cue(unsigned char mode)
{
 audio_game_stop_sample(g_frame_actor_speed_cue_handle);
 switch(mode) {
 case 1:g_frame_actor_speed_cue_handle=audio_play_animation_cue(74);break;
 case 2:g_frame_actor_speed_cue_handle=audio_play_animation_cue(75);break;
 case 3:g_frame_actor_speed_cue_handle=audio_play_animation_cue(76);break;
 default:audio_game_stop_sample(g_frame_actor_speed_cue_handle);break;
 }
 g_frame_actor_speed_cue_mode=mode;
}
