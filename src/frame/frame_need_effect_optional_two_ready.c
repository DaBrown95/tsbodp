#include "frame_need_effect_optional_selection.h"

unsigned int frame_need_effect_optional_two_ready(struct FrameNeedEffectState *state,
                                                  int threshold)
{
    if (state->optional == 2 && *(short *)&state->parameter >= threshold)
        return 1;
    return 0;
}
asm(".align 2, 0");
