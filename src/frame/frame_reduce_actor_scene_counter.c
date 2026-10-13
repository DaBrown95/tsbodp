#include "frame_actor_scene.h"
void frame_reduce_actor_scene_counter(void)
{
 ((struct FrameActorSceneState *)&g_resource_game_state)->counter=(int)(unsigned int)(((struct FrameActorSceneState *)&g_resource_game_state)->counter+((struct FrameActorSceneState *)&g_resource_game_state)->counter*0.1);
}
