#include "frame_need_effect_optional_selection.h"

unsigned int frame_select_optional_attachment_kinds_432cc(struct FrameNeedEffectState *state,
                                                          unsigned char *out)
{
    unsigned int count = 0;
    switch (state->optional) {
    default:
        {
            unsigned int period = display_time_period(&g_display_world_clock);
            unsigned char kind;
            switch (period) {
            case 0: kind = 28; break;
            case 1: kind = 32; break;
            case 2: kind = 30; break;
            case 3: kind = 31; break;
            default: kind = 0; break;
            }
            out[count] = kind;
            count++;
        }
        break;
    case 1:
        out[0] = 45;
        count = 1;
        break;
    case 3:
        out[0] = 22;
        count = 1;
        break;
    }
    if (state->optional == 2 && (short)state->parameter > 10240)
        out[count] = 12;
    return 1;
}
