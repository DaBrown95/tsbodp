#include "frame_actor_attachment_control_jobs.h"

unsigned int frame_prepare_attachment_control_jobs(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 45:
    case 56:
    case 57:
    case 98:
    case 99:
    case 100:
    case 101:
        return 1;
    default:
        return 1;
    }
}
