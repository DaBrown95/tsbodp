#include "frame_actor_attachment_job_87.h"

unsigned int frame_dispatch_attachment_job_87(struct FrameNeedEffectState *owner,
                                              struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;
    switch (job->kind) {
    case 92:
    case 93:
    case 94:
    case 95:
    case 96:
    case 97:
        result = frame_step_attachment_job_87(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}
