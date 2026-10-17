#include "display_actor_interaction.h"

unsigned int frame_interaction_dispatch_31(struct FrameNeedEffectState *owner,
                                           struct FrameObject *object)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, object);
    unsigned int result;
    if (job->kind == 49) result = frame_interaction_step_31(owner, job);
    else result = 0;
    return result;
}
