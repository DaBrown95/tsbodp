#include "frame_actor_needs.h"
void frame_save_actor_needs(struct FrameActorNeedState *state)
{
 unsigned int i;
 int value;
 for (i=0; i<8; i++) { value = state->values[i] >> 16; frame_write_save_value(&value, 2); }
}
