#include "frame_actor_attachment_jobs_88_89.h"

unsigned int frame_dispatch_attachment_jobs_88_89(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    switch (job->kind) {
    case 88:
        return frame_step_attachment_job_88(owner, job);
    case 89:
        return frame_step_attachment_job_89(owner, job);
    }
    return 0;
}
