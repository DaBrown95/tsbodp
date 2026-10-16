#include "frame_actor_attachment_jobs_64_66.h"

unsigned int frame_prepare_attachment_jobs_64_66(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 64:
    case 65:
    case 66:
        return 1;
    default:
        return 1;
    }
}
