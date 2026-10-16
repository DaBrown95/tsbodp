#include "frame_parameter_stage_jobs.h"

unsigned int frame_dispatch_parameter_stage_jobs(struct FrameNeedEffectState *owner,
                                                   struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    unsigned int result;
    if (job->timer == 0)
        frame_set_actor_direction(job->actor,
            frame_direction_to_need_effect_center(job->actor, owner));
    switch (job->kind) {
    case 7:
        result = frame_step_parameter_stage_job_7(owner, job);
        break;
    case 91:
        result = frame_step_parameter_stage_job_91(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}
