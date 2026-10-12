#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
void frame_point_to_integer(const struct FramePoint *input,struct FramePoint *output) { output->x=((const short*)input)[1]; output->y=((const short*)input)[3]; }
asm(".align 2, 0");
