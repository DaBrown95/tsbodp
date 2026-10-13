#include "frame_optional_choice_context.h"

unsigned int frame_initialize_optional_choice_context(struct FrameNeedEffectState *owner)
{
    ((struct FrameOptionalChoiceContextState *)owner)->active = 0;
    return 1;
}
asm(".align 2, 0");
