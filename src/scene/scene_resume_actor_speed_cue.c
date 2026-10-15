#include "scene_resume.h"
#include "frame_scene_player.h"
#include "frame_actor_speed.h"
void scene_resume_actor_speed_cue(void)
{
 if(g_frame_scene_player_mode.mode==1)
  frame_actor_set_speed_cue(g_frame_actor_speed_cue_mode);
}
