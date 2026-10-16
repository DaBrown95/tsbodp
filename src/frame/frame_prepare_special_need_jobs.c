#include "frame_special_need_jobs.h"

unsigned int frame_prepare_special_need_jobs(struct FrameNeedEffectState *owner,
                                              struct FrameObject *actor,
                                              unsigned int kind)
{
    switch (kind) {
    case 7:
    case 45:
        return 1;
    default:
        return 1;
    }
}
