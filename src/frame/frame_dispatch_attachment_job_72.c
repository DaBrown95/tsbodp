#include "frame_actor_attachment_job_72.h"

unsigned int frame_dispatch_attachment_job_72(struct FrameNeedEffectState *owner,
                                              struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;
    switch (job->kind) {
    case 72:
        result = frame_step_attachment_job_72(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}
