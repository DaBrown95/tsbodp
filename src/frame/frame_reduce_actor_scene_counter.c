#include "frame_actor_scene.h"
void frame_reduce_actor_scene_counter(void)
{
 ((struct FrameActorSceneState *)&g_resource_game_state)->counter.value=(int)(unsigned int)(((struct FrameActorSceneState *)&g_resource_game_state)->counter.value+((struct FrameActorSceneState *)&g_resource_game_state)->counter.value*0.1);
}
