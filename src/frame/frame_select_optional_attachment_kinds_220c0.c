#include "frame_need_effect_optional_jobs.h"

unsigned int frame_select_optional_attachment_kinds_220c0(struct FrameNeedEffectState *state,
                                                          unsigned char *out)
{
    unsigned int count = 0;
    switch (state->optional) {
    case 4:
        out = (unsigned char *)((unsigned int)out | count);
        *out = 92;
        break;
    case 5:
        out = (unsigned char *)((unsigned int)out | count);
        *out = 93;
        break;
    case 6:
        out = (unsigned char *)((unsigned int)out | count);
        *out = 94;
        break;
    case 7:
        out = (unsigned char *)((unsigned int)out | count);
        *out = 95;
        break;
    case 8:
        out = (unsigned char *)((unsigned int)out | count);
        *out = 96;
        break;
    case 9:
        out = (unsigned char *)((unsigned int)out | count);
        *out = 97;
        break;
    default:
        break;
    }
    return 1;
}
asm(".align 2, 0");
