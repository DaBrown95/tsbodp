#include "frame_route_attachment_21_45.h"

unsigned int frame_dispatch_route_attachment_21_45(struct FrameNeedEffectState *owner,
                                                   struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(owner, actor);
    unsigned int result;
    switch (job->kind) {
        case 21:
            result = frame_step_route_attachment_21(owner, job);
            break;
        case 45:
            result = frame_step_route_attachment_45_without_actor_effect(owner, job);
            break;
        default:
            result = 0;
            break;
    }
    return result;
}
