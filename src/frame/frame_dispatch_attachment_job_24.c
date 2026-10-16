#include "frame_actor_attachment_job_24.h"

unsigned int frame_dispatch_attachment_job_24(struct FrameNeedEffectState *owner,
                                              struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    unsigned int result;
    if (job->timer == 0) {
        struct FrameObject *attached = job->actor;
        frame_set_actor_direction(attached, frame_direction_to_need_effect_center(attached, owner));
    }
    if (job->kind == 24)
        result = frame_step_attachment_job_24(owner, job);
    else
        result = 0;
    return result;
}
asm(".align 2, 0");
