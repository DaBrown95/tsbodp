#include "frame_actor_needs.h"
void frame_update_actor_needs(struct FrameActorNeedTickState *state, struct FrameActorObject *object)
{
 unsigned int i; unsigned char *paused;
 if (!(g_frame_actor_need_input.views[g_frame_actor_need_input.local_player].flags & 4) && object->variant_state != 6) {
  i = 0;
  paused = &g_frame_actor_needs_paused;
  for (; i < 8; i++) {
   if (!*paused || i == 6) {
    state->values[i] = state->values[i] + frame_actor_need_delta((struct FrameActorNeedState *)state, i, (struct FrameObject *)object) <= 0 ? 0 :
      state->values[i] + frame_actor_need_delta((struct FrameActorNeedState *)state, i, (struct FrameObject *)object) > 0x63ffffff ? 0x64000000 :
      state->values[i] + frame_actor_need_delta((struct FrameActorNeedState *)state, i, (struct FrameObject *)object);
   }
  }
  for (i = 0; i < 8; i++) if (state->values[i] > 0x14000000) state->started &= ~(1U << i);
 }
}
asm(".align 2, 0");
