#include "frame_actor_attachment_jobs_60_63.h"
unsigned int frame_prepare_attachment_jobs_60_63(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor,
                                                 unsigned int kind)
{
    switch (kind) {
    case 60:
    case 63:
        return 1;
    default:
        return 1;
    }
}
