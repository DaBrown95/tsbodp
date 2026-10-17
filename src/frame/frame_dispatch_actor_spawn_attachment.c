#include "frame_actor_spawn_attachment.h"

unsigned int frame_dispatch_actor_spawn_attachment(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;
    if (job->kind == 87)
        result = frame_step_actor_spawn_attachment(owner, job);
    else
        result = 0;
    return result;
}
