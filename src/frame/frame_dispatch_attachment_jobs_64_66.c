#include "frame_actor_attachment_jobs_64_66.h"

unsigned int frame_dispatch_attachment_jobs_64_66(struct FrameNeedEffectState *owner,
                                                   struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;
    switch (job->kind) {
    case 64:
    case 65:
        result = frame_step_attachment_jobs_64_65(owner, job);
        break;
    case 66:
        result = frame_step_attachment_job_66(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}
asm(".align 2, 0");
