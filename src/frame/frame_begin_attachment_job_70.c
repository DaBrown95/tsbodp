#include "frame_actor_attachment_job_70.h"

unsigned int frame_begin_attachment_job_70(struct FrameNeedEffectState *owner,
                                           struct FrameObject *actor,
                                           unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    struct FramePoint point;
    unsigned int result;
    if (job) {
        job->kind = kind;
        if (actor->id == 0)
            frame_attachment_position(owner->object, 0, &point);
        else
            frame_attachment_position(owner->object, 1, &point);
        frame_begin_actor_route(actor, &point, &job->status, 0, 1);
        frame_request_animation((struct FrameCommandObject *)actor, 6);
        result = 1;
    } else
        result = 0;
    return result;
}
asm(".align 2, 0");
