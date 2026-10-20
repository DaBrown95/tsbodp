#include "frame_optional_activation.h"

unsigned int frame_initialize_optional_activation_context(struct FrameNeedEffectState *owner)
{
    ((struct FrameOptionalChoiceContextState *)owner)->active = 0;
    return 1;
}
asm(".align 2, 0");
