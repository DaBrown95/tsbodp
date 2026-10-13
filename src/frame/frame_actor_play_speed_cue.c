#include "audio_game.h"
#include "frame_actor_speed.h"
void frame_actor_play_speed_cue(unsigned int cue,unsigned char mode)
{
 audio_game_stop_sample(g_frame_actor_speed_cue_handle);
 g_frame_actor_speed_cue_handle=audio_play_animation_cue(cue);
 g_frame_actor_speed_cue_mode=mode;
}
