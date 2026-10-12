#include "frame_actor_needs.h"
unsigned int frame_empty_need_mask(struct FrameActorNeedState *state)
{
 unsigned int mask = 0;
 FrameU8 i;
 for (i = 0; i < 8; i++) if (!state->values[i]) mask |= 1U << i;
 return mask;
}
