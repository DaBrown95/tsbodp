#include "frame_actor_attachment_job_75.h"
unsigned int frame_dispatch_attachment_job_75(struct FrameNeedEffectState *owner,
                                             struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;
    if (job->kind == 75) result = frame_step_attachment_job_75(owner, job);
    else result = 0;
    return result;
}
