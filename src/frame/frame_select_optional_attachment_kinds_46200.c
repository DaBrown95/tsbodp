#include "frame_need_effect_optional_selection.h"

unsigned int frame_select_optional_attachment_kinds_46200(struct FrameNeedEffectState *state,
                                                          unsigned char *out)
{
    unsigned int count = 0;
    if (!(unsigned char)frame_need_effect_optional_one_ready(state))
        out[count++] = 59;
    else
        out[count++] = 45;
    if ((unsigned char)frame_need_effect_optional_two_ready(state, 10240))
        out[count] = 12;
    return 1;
}
