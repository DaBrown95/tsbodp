#include "frame_route_attachment_49.h"
#include "display_actor_interaction.h"

unsigned int frame_dispatch_route_attachment_49_259f0(struct FrameNeedEffectState *owner,
    struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job =
        frame_find_actor_attachment_record(owner, actor);
    unsigned int result;
    if (job->kind == 49)
        result = frame_step_route_attachment_49_258c4(owner, job);
    else
        result = 0;
    return result;
}
