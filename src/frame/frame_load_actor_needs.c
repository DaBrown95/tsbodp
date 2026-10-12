#include "frame_actor_needs.h"
void frame_load_actor_needs(struct FrameActorNeedState *state)
{
 unsigned int i;
 int value;
 for (i=0; i<8; i++) { frame_load_save_value(&value, 2); state->values[i] = value << 16; }
}
