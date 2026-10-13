#include "frame_need_effect_optional_jobs.h"

unsigned int frame_need_effect_optional_one_ready(struct FrameNeedEffectState *state)
{
    if (state->optional == 1 && *(short *)&state->parameter >= 0)
        return 1;
    return 0;
}
asm(".align 2, 0");
