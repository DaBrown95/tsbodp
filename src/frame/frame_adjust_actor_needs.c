#include "frame_actor_needs.h"
void frame_adjust_actor_needs(struct FrameActorNeedState *state, unsigned int kind, FrameU8 multiplier)
{
 struct FrameActorNeedState *player = ((struct FrameActorObject *)g_frame_actor_need_input.views[0].actor)->actor_state;
 unsigned int i;
 if (!(g_frame_actor_need_input.views[g_frame_actor_need_input.local_player].flags & 4) && state) {
  for (i = 0; i < 8; i++) {
   int adjustment;
   if (g_frame_actor_need_adjustments[kind][i] > 0) {
    int factor = g_frame_actor_need_multipliers[multiplier] >> 8;
    adjustment = frame_fixed_multiply(g_frame_actor_need_adjustments[kind][i] >> 8, factor); adjustment <<= 8;
   }
   else adjustment = g_frame_actor_need_adjustments[kind][i];
   state->values[i] += adjustment;
   if (state->values[i] < 0) state->values[i] = 0;
   if (state->values[i] > 0x64000000) state->values[i] = 0x64000000;
   if (g_frame_actor_need_adjustments[kind][i] > 0 && player == state)
    g_frame_actor_need_ui[g_frame_actor_need_input.local_player].changed |= 0x400U << i;
  }
 }
}
asm(".align 2, 0");
