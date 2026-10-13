#include "frame_scene_player.h"
#include "frame_actor_speed.h"
#include "audio_game.h"
#include "scene_retention.h"
void scene_stop_actor_speed_cue(void)
{
 if(g_frame_scene_player_mode.mode==1)audio_game_stop_sample(g_frame_actor_speed_cue_handle);
}
