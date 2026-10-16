#include "frame_actor_attachment_jobs_45_90.h"
unsigned int frame_prepare_attachment_jobs_45_90(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 45:
    case 90:
        return 1;
    default:
        return 1;
    }
}
