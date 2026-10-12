#include "frame_actor_needs.h"
void *frame_initialize_actor_state(FrameU32 actor_id)
{
 struct FrameActorNeedState *state = &g_frame_actor_need_states[actor_id - 32];
 state->values[0] = frame_random_range(5, 60) << 24;
 state->values[1] = frame_random_range(5, 60) << 24;
 state->values[2] = frame_random_range(5, 60) << 24;
 state->values[3] = frame_random_range(5, 60) << 24;
 state->values[4] = frame_random_range(5, 60) << 24;
 state->values[5] = frame_random_range(5, 60) << 24;
 state->values[6] = frame_random_range(5, 60) << 24;
 state->values[7] = frame_random_range(5, 60) << 24;
 return state;
}
