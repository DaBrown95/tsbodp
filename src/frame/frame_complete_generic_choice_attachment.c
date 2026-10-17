#include "frame_actor_attachment_generic_choice.h"

unsigned int frame_complete_generic_choice_attachment(struct FrameNeedEffectState *owner, struct FrameObject *actor)
{
    unsigned int result = 1;
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    if (job->kind != 40)
        result = 0;
    return result;
}
