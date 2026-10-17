#include "frame_actor_attachment_palette_jobs.h"

unsigned int frame_begin_attachment_palette_jobs(struct FrameNeedEffectState *owner,
                                           struct FrameObject *actor,
                                           unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        owner, actor);
    unsigned int result;
    if (!job)
        result = 0;
    else {
        job->kind = kind;
        result = 1;
    }
    return result;
}
asm(".align 2, 0");
