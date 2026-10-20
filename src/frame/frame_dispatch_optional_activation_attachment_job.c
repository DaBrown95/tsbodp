#include "frame_optional_activation.h"

unsigned int frame_dispatch_optional_activation_attachment_job(struct FrameNeedEffectState *owner,
    struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(owner, actor);

    switch (job->kind) {
    case 82:
        return frame_step_optional_activation_job_82_86(owner, job, 0);
    case 83:
        return frame_step_optional_activation_job_83_84(owner, job, 0);
    case 84:
        return frame_step_optional_activation_job_83_84(owner, job, 1);
    case 85:
        return frame_step_optional_activation_job_85(owner, job);
    case 86:
        return frame_step_optional_activation_job_82_86(owner, job, 1);
    default:
        return 0;
    }
}
asm(".align 2, 0");
