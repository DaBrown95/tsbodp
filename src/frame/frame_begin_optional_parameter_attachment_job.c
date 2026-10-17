#include "frame_need_effect_optional_completion.h"

unsigned int frame_begin_optional_parameter_attachment_job(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor,
                                                  unsigned int kind)
{
    struct FramePoint point;
    struct FrameActorAttachmentRecord *job =
        frame_allocate_actor_attachment_record(owner,
                                               actor);
    if (job) {
        job->kind = kind;
        frame_attachment_position(owner->object, 0, &point);
        frame_begin_actor_route(actor, &point, &job->status, 4, 1);
        frame_request_animation((struct FrameCommandObject *)actor, 6);
        return 1;
    } else
        return 0;
}
