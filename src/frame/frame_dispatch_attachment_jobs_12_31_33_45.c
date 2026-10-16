#include "frame_actor_attachment_jobs_12_31_33_45.h"


unsigned int frame_dispatch_attachment_jobs_12_31_33_45(struct FrameNeedEffectState *owner,
                                                       struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    unsigned int result;
    switch (job->kind) {
    case 31:
    case 33:
        result = frame_step_attachment_jobs_31_33(owner, job);
        break;
    case 12:
        result = frame_step_attachment_job_12_358b0(owner, job);
        break;
    case 45:
        result = frame_step_attachment_job_45_3594c(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}
