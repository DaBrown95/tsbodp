#include "frame_actor_attachment_jobs_60_63.h"
unsigned int frame_dispatch_attachment_jobs_60_63(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    if (job->timer == 0) {
        struct FrameObject *target = job->actor;
        frame_set_actor_direction(target, frame_direction_to_need_effect_center(target, owner));
    }
    switch (job->kind) {
    case 60: return frame_step_attachment_job_60(owner, job);
    case 63: return frame_step_attachment_job_63(owner, job);
    default: return 0;
    }
}
