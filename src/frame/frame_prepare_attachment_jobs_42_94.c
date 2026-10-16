#include "frame_actor_attachment_jobs_42_94_callbacks.h"

unsigned int frame_prepare_attachment_jobs_42_94(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 42:
    case 94:
        return 1;
    default:
        return 1;
    }
}
