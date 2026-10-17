#include "frame_actor_attachment_jobs_79_80.h"

unsigned int frame_dispatch_attachment_jobs_79_80(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;
    if (job->timer == 0) {
        struct FrameObject *attached = job->actor;
        frame_set_actor_direction(attached, frame_direction_to_need_effect_center(attached, owner));
    }
    switch (job->kind) {
    case 79:
        result = frame_step_attachment_jobs_79_80(owner, job, 0);
        break;
    case 80:
        result = frame_step_attachment_jobs_79_80(owner, job, 1);
        break;
    default:
        result = 0;
    }
    return result;
}
