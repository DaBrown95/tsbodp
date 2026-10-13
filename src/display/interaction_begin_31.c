#include "display_actor_interaction.h"

unsigned char frame_interaction_begin_31(struct FrameNeedEffectState *owner,
                                         struct FrameObject *object, unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, object);
    struct FramePoint point;
    unsigned char result;
    if (!job) result = 0;
    else {
        job->unknown04 = kind;
        frame_attachment_position(owner->object, 2, &point);
        frame_begin_actor_route(object, &point, &job->status, 0, 1);
        frame_request_animation((struct FrameCommandObject *)object, 6);
        result = 1;
    }
    return result;
}
