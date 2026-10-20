#include "frame_optional_activation.h"

unsigned int frame_select_optional_activation_attachment_kind(struct FrameNeedEffectState *owner,
    unsigned char *out)
{
    if (!((struct FrameOptionalChoiceContextState *)owner)->active)
        *out = 82;
    else
        *out = 86;
    return 1;
}
