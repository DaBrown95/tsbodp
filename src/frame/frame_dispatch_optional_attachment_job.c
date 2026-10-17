#include "frame_need_effect_optional_jobs.h"

unsigned int frame_dispatch_optional_attachment_job(struct FrameNeedEffectState *owner,
                                                     struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job =
        frame_find_actor_attachment_record(owner,
                                           actor);
    switch (job->kind) {
    case 29:
        return frame_step_optional_animation_attachment_job(owner, job);
    case 45:
        return frame_step_optional_attachment_job(owner, job);
    }
    return 0;
}
