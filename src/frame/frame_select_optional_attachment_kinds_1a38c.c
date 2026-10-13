#include "frame_need_effect_optional_selection.h"

unsigned int frame_select_optional_attachment_kinds_1a38c(struct FrameNeedEffectState *state,
                                                          unsigned char *out)
{
    out[0] = 60;
    out[1] = 23;
    if ((unsigned char)frame_need_effect_optional_two_ready(state, 10240))
        out[2] = 12;
    return 1;
}
asm(".align 2, 0");
