#include "frame_need_effect_condition_jobs.h"

unsigned int frame_prepare_condition_attachment_jobs(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 7:
    case 44:
    case 45:
        return 1;
    default:
        return 1;
    }
}
