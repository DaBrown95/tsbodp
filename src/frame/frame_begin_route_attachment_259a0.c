#include "display_actor_interaction.h"

unsigned int frame_begin_route_attachment_259a0(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    struct FramePoint point;
    struct FrameActorAttachmentRecord *job =
        frame_allocate_actor_attachment_record(owner,
                                               actor);
    if (job) {
        unsigned char attachment;
        job->kind = kind;
        attachment = 0;
        if (kind == 49)
            attachment = 1;
        frame_attachment_position(owner->object, attachment, &point);
        frame_begin_actor_route(actor, &point, &job->status, 4, 1);
        frame_request_animation((struct FrameCommandObject *)actor, 6);
        return 1;
    } else
        return 0;
}
asm(".align 2, 0");
