#include "frame_need_effect_optional_jobs.h"

unsigned int frame_prepare_optional_attachment_kind(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 29:
    case 45:
        return 1;
    default:
        return 1;
    }
}
