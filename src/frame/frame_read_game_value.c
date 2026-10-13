#include "frame_optional_choice_apply.h"
#include "frame_actor_actions.h"

int frame_read_game_value(void)
{
    return ((struct FrameActorValueWorld *)&g_resource_game_state)->value;
}
asm(".align 2, 0");
