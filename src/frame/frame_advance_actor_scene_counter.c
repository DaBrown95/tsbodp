#include "frame_actor_scene.h"
void frame_advance_actor_scene_counter(void)
{
 ((struct FrameActorSceneState *)&g_resource_game_state)->counter.value+=20;
}
