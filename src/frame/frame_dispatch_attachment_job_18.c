#include "display_actor_interaction.h"
#include "frame_actor_attachment_job_18.h"

unsigned int frame_dispatch_attachment_job_18(struct FrameNeedEffectState *owner,
                                              struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    unsigned int result;
    if (job->kind == 18) result = frame_step_attachment_job_18(owner, job);
    else result = 0;
    return result;
}
