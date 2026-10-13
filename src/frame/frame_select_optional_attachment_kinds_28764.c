#include "frame_need_effect_optional_selection.h"

unsigned int frame_select_optional_attachment_kinds_28764(struct FrameNeedEffectState *state,
                                                          unsigned char *out)
{
    unsigned int count = 0;
    if (!(unsigned char)frame_need_effect_optional_one_ready(state)) {
        unsigned int period = display_time_period(&g_display_world_clock);
        out[0] = 31;
        if (period <= 2) {
            unsigned char kind;
            out[0] = 33;
            count = 1;
            switch (period) {
            case 0: kind = 28; break;
            case 1: kind = 32; break;
            case 2: kind = 30; break;
            default: kind = 0; break;
            }
            out[count] = kind;
            count++;
        }
    } else {
        out[0] = 45;
        count = 1;
    }
    if ((unsigned char)frame_need_effect_optional_two_ready(state, 10240))
        out[count] = 12;
    return 1;
}
asm(".align 2, 0");
