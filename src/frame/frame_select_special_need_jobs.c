#include "frame_special_need_jobs.h"

unsigned int frame_select_special_need_jobs(struct FrameNeedEffectState *owner,
                                             unsigned char *choices)
{
    if (!(unsigned char)frame_need_effect_optional_one_ready(owner))
        choices[0] = 7;
    else
        choices[0] = 45;
    return 1;
}
asm(".align 2,0");
