#include "frame_actor_attachment_jobs_16_17.h"

unsigned int frame_dispatch_attachment_jobs_16_17(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner,actor);
    unsigned int result;
    switch(job->kind) {
    case 16:
        result = frame_step_attachment_job_16_2bccc(owner,job);
        break;
    case 17:
        result = frame_step_attachment_job_17_2bd38(owner,job);
        break;
    default:
        result = 0;
        break;
    }
    return result;
}
