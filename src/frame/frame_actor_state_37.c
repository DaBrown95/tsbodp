#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_scene.h"
void frame_actor_state_37(void)
{
 if(((struct FrameActorSceneState*)&g_resource_game_state)->timer>-2) {
  g_scene_mode_bytes[0]=0;
  resource_submit_scene(1,0,37);
 } else if(((struct FrameActorSceneState*)&g_resource_game_state)->stage<=1) {
  ((struct FrameActorSceneState*)&g_resource_game_state)->ready=1;
  g_scene_mode_bytes[0]=1;
  resource_submit_scene(1,0,28);
 } else if(((struct FrameActorSceneState*)&g_resource_game_state)->stage<=4) {
  ((struct FrameActorSceneState*)&g_resource_game_state)->ready=1;
  frame_advance_actor_scene_counter();
  g_scene_mode_bytes[0]=2;
  resource_submit_scene(1,0,36);
 }
 frame_reset_actor_needs((struct FrameActorNeedState*)((unsigned int)&g_resource_game_state+0xb0));
}
