#include "frame_actor_attachment_jobs_16_17.h"

unsigned int frame_prepare_attachment_jobs_16_17(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor,
                                                 unsigned int kind)
{
    switch(kind) {
    case 16:
        return 1;
    case 17:
        return 1;
    default:
        return 1;
    }
}
