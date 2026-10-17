#include "frame_route_attachment_21_45.h"

unsigned int frame_select_route_attachment_12b2c(struct FrameNeedEffectState *owner,
                                                           unsigned char *out)
{
    if (!(unsigned char)frame_need_effect_optional_one_ready(owner))
        *out = 21;
    else
        *out = 45;
    return 1;
}
asm(".align 2, 0");
