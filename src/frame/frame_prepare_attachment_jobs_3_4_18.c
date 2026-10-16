#include "frame_actor_attachment_jobs_3_4_18.h"

unsigned int frame_prepare_attachment_jobs_3_4_18(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor,
                                                 unsigned int kind)
{
    switch (kind) {
    case 3:
        return 1;
    case 4:
        return 1;
    case 18:
        return 1;
    default:
        return 1;
    }
}
