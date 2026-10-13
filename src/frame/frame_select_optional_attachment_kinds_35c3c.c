#include "frame_need_effect_optional_selection.h"

unsigned int frame_select_optional_attachment_kinds_35c3c(struct FrameNeedEffectState *state,
                                                          unsigned char *out)
{
    unsigned int count = 0;
    if (!(unsigned char)frame_need_effect_optional_one_ready(state)) {
        unsigned int period = display_time_period(&g_display_world_clock);
        unsigned char kind;
        switch (period) {
        case 0: case 1: case 2: kind = 33; break;
        case 3: kind = 31; break;
        default: kind = 0; break;
        }
        out[count] = kind;
        count++;
    } else {
        out[0] = 45;
        count = 1;
    }
    if ((unsigned char)frame_need_effect_optional_two_ready(state, 10240))
        out[count] = 12;
    return 1;
}
asm(".align 2, 0");
