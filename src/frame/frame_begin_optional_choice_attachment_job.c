#include "frame_optional_choice_context.h"

unsigned int frame_begin_optional_choice_attachment_job(struct FrameNeedEffectState *owner,
                                                         struct FrameObject *object,
                                                         unsigned int kind)
{
    struct FrameActorAttachmentRecord *job =
        frame_allocate_actor_attachment_record(owner, object);
    unsigned int result;
    if (!job)
        result = 0;
    else {
        job->kind = kind;
        ((struct FrameOptionalChoiceContextState *)owner)->active = 1;
        result = 1;
    }
    return result;
}
asm(".align 2, 0");
