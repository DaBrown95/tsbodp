#include "display_actor_interaction.h"
#include "frame_actor_target_jobs.h"

unsigned char frame_begin_attachment_route_3(struct FrameNeedEffectState *owner,
                                               struct FrameObject *actor,
                                               unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    struct FramePoint point;
    unsigned char result;
    if (!job) result = 0;
    else {
        job->kind = kind;
        frame_attachment_position(owner->object, 0, &point);
        frame_begin_actor_route(actor, &point, &job->status, 3, 1);
        frame_request_animation((struct FrameCommandObject *)actor, 6);
        result = 1;
    }
    return result;
}
