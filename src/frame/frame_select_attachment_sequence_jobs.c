#include "frame_actor_attachment_sequence_jobs.h"

unsigned int frame_select_attachment_sequence_jobs(struct FrameNeedEffectState *owner,
                                                   unsigned char *out)
{
    if ((unsigned char)frame_need_effect_optional_one_ready(owner) == 0) {
        short parameter = (short)owner->parameter;
        if (parameter == 0) {
            out[0] = 57;
        } else {
            out[0] = 56;
            out[1] = 18;
            if (parameter != 0xa00)
                out[2] = 5;
            else
                out[2] = 2;
        }
    } else {
        out[0] = 45;
    }
    return 1;
}
