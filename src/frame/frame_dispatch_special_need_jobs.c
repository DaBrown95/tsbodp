#include "frame_special_need_jobs.h"

unsigned int frame_dispatch_special_need_jobs(struct FrameNeedEffectState *owner,
                                               struct FrameObject *actor)
{
    unsigned int result = 0;
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    if (job->timer == 0)
        frame_set_actor_direction(job->actor,
            frame_direction_to_need_effect_center(job->actor, owner));
    switch (job->kind) {
    case 45:
        result = frame_step_special_need_job_45(owner, job);
        break;
    case 7:
        result = frame_step_special_need_job_7(owner, job);
        break;
    }
    return result;
}
asm(".align 2,0");
