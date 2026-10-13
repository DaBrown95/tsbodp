#include "frame_optional_choice_context.h"

unsigned int frame_dispatch_optional_choice_attachment_job(struct FrameNeedEffectState *owner,
                                                            struct FrameObject *object)
{
    struct FrameActorAttachmentRecord *job =
        frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner, object);
    unsigned int result;
    switch (job->kind) {
    case 41:
        result = frame_step_optional_choice_attachment_job(owner, job);
        break;
    case 45:
        result = frame_step_optional_choice_kind_45(owner, job);
        break;
    default:
        result = 0;
        break;
    }
    if (result == 2 || result == 0)
        ((struct FrameOptionalChoiceContextState *)owner)->active = 0;
    return result;
}
