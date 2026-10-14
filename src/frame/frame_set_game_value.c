#include "frame_game_value.h"
#include "frame_actor_actions.h"
#include "frame_actor_scene.h"

void frame_set_game_value(int value)
{
    ((struct FrameActorValueWorld *)&g_resource_game_state)->value = value;
}
