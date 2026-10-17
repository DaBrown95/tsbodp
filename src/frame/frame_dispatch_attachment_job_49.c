#include "display_actor_interaction.h"
#include "frame_actor_target_jobs.h"

unsigned int frame_dispatch_attachment_job_49(struct FrameNeedEffectState *owner,
                                               struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;
    if (job->kind == 49) result = frame_interaction_step_16c68(owner, job);
    else result = 0;
    return result;
}
