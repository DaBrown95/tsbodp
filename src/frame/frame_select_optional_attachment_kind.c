#include "frame_need_effect_optional_jobs.h"

unsigned int frame_select_optional_attachment_kind(struct FrameNeedEffectState *owner,
                                                    unsigned char *out)
{
    if (!(unsigned char)frame_need_effect_optional_one_ready(owner))
        *out = 29;
    else
        *out = 45;
    return 1;
}
asm(".align 2, 0");
