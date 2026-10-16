#include "frame_actor_attachment_timed_job_12.h"

unsigned int frame_dispatch_timed_attachment_job_12(struct FrameNeedEffectState *owner,
                                                    struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner,actor);
    unsigned int result;
    if (job->kind == 12) result = frame_step_timed_attachment_job_12(owner,job);
    else result = 0;
    return result;
}
