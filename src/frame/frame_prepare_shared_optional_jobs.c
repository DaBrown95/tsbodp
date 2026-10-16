#include "frame_shared_optional_jobs.h"

unsigned int frame_prepare_shared_optional_jobs(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 45:
    case 61:
        return 1;
    default:
        return 1;
    }
}
