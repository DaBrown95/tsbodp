#include "frame_actor_scene.h"
#include "frame_actor_idle.h"
void frame_add_actor_scene_counter_rate(void)
{
 ((struct FrameActorSceneState *)&g_resource_game_state)->counter.value+=g_actor_scene_counter_rates[((struct FrameActorSceneState *)&g_resource_game_state)->stage];
}
