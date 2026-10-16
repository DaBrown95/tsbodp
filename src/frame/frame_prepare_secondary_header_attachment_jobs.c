#include "frame_need_effect_secondary_header_jobs.h"

unsigned int frame_prepare_secondary_header_attachment_jobs(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 27:
    case 50:
        return 1;
    default:
        return 1;
    }
}
