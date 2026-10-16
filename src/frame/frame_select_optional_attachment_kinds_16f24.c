#include "frame_need_effect_optional_jobs.h"

unsigned int frame_select_optional_attachment_kinds_16f24(struct FrameNeedEffectState *state,
                                                          unsigned char *out)
{
    if ((unsigned char)frame_need_effect_optional_one_ready(state) == 0) {
        if ((short)state->parameter == 0) {
            out[0] = 57;
        } else {
            unsigned char kind;
            out[0] = 56;
            out[1] = 100;
            switch ((short)state->parameter) {
            case 0xA00:
                kind = 99;
                goto append_101;
            case 0xB00:
                kind = 98;
            append_101:
                out[2] = kind;
                out[3] = 101;
                break;
            case 0xC00:
                out[2] = 99;
                out[3] = 98;
                break;
            }
        }
    } else {
        out[0] = 45;
    }
    return 1;
}
