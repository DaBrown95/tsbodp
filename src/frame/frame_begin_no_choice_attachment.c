#include "frame_actor_attachment_no_choice.h"

unsigned int frame_begin_no_choice_attachment(struct FrameNeedEffectState *owner,
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
asm(".align 2, 0");
