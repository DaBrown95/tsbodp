#include "frame_actor_attachment_jobs_45_56_57.h"

unsigned int frame_dispatch_attachment_jobs_45_56_57(struct FrameNeedEffectState *owner,
                                                     struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    if (job->timer == 0) {
        struct FrameObject *object = job->actor;
        frame_set_actor_direction(object, frame_direction_to_need_effect_center(object, owner));
    }
    switch (job->kind) {
    case 57:
        return frame_step_attachment_modes_56_57_23ec4(owner, job, 0x100);
    case 56:
        return frame_step_attachment_modes_56_57_23ec4(owner, job, 0x200);
    case 45:
        return frame_step_optional_attachment_job_45_23d00(owner, job);
    default:
        return 0;
    }
}
