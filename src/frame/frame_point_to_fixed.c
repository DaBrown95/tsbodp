#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
void frame_point_to_fixed(const struct FramePoint *input,struct FramePoint *output) { output->x=input->x<<16; output->y=input->y<<16; }
asm(".align 2, 0");
