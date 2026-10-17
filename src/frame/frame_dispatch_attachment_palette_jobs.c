#include "frame_actor_attachment_palette_jobs.h"

unsigned int frame_dispatch_attachment_palette_jobs(struct FrameNeedEffectState *owner,
                                                     struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    switch (job->kind) {
    case 9:
        return frame_step_attachment_palette_job_9(owner, job);
    case 8:
    case 11:
        return frame_step_attachment_palette_jobs_8_11(owner, job);
    case 10:
        return frame_step_attachment_palette_job_10(owner, job);
    default:
        return 0;
    }
}
