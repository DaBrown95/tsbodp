#include "frame_actor_attachment_timed_job_12.h"

unsigned int frame_begin_timed_attachment_job_12(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor,unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner,actor);
    unsigned int result;
    if (!job) result = 0;
    else {
        job->kind = kind;
        result = 1;
    }
    return result;
}
asm(".align 2,0");
