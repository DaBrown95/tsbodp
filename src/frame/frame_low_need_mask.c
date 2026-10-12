#include "frame_actor_needs.h"
unsigned int frame_low_need_mask(struct FrameActorNeedState *state, unsigned int enabled)
{
 unsigned int mask = 0;
 FrameU8 i;
 if (g_frame_actor_need_input.views[g_frame_actor_need_input.local_player].flags & 4) return 0;
 for (i = 0; i < 8; i++) { unsigned int bit = 1U << i; if ((enabled & bit) && state->values[i] <= 0x13ffffff) mask |= bit; }
 return mask;
}
