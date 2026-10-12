#include "frame_actor_needs.h"
void frame_reset_actor_needs(struct FrameActorNeedState *state)
{
 frame_copy_bytes(state, &g_frame_actor_need_defaults, sizeof(*state));
 state->selected = 0;
}
asm(".align 2, 0");
