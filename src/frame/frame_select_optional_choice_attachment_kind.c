#include "frame_optional_choice_context.h"

unsigned int frame_select_optional_choice_attachment_kind(struct FrameNeedEffectState *owner,
                                                           unsigned char *out)
{
    if (!(unsigned char)frame_need_effect_optional_one_ready(owner))
        *out = 41;
    else
        *out = 45;
    return 1;
}
asm(".align 2, 0");
