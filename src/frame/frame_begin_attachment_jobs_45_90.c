#include "frame_actor_attachment_jobs_45_90.h"
unsigned int frame_begin_attachment_jobs_45_90(struct FrameNeedEffectState *owner,
                                              struct FrameObject *actor,
                                              unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    unsigned int result;
    if (!job)
        result = 0;
    else {
        job->kind = kind;
        result = 1;
    }
    return result;
}
asm(".align 2,0");
