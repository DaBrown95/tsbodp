#include "frame_actor_attachment_jobs_13_14.h"
unsigned int frame_dispatch_attachment_jobs_13_14(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    switch (job->kind) {
    case 13:
    case 14:
        return frame_step_attachment_jobs_13_14(owner, job);
    default:
        return 0;
    }
}
