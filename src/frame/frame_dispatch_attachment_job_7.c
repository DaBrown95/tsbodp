#include "display_actor_interaction.h"
#include "frame_actor_target_jobs.h"

unsigned int frame_dispatch_attachment_job_7(struct FrameNeedEffectState *owner,
                                              struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    unsigned int result;
    if (job->kind == 7) result = frame_step_attachment_job_7(owner, job);
    else result = 0;
    return result;
}
