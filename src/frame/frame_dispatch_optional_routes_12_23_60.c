#include "frame_optional_routes_12_23_60.h"

unsigned int frame_dispatch_optional_routes_12_23_60(struct FrameNeedEffectState *owner,
                                                    struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(owner, actor);
    unsigned int result;
    if (job->timer == 0) {
        struct FrameObject *attached_actor = job->actor;
        frame_set_actor_direction(attached_actor,
            frame_direction_to_need_effect_center(attached_actor, owner));
    }
    switch (job->kind) {
    case 60:
        result = frame_step_optional_route_kind_60(owner, job);
        break;
    case 23:
        result = frame_step_optional_route_kind_23(owner, job);
        break;
    case 12:
        result = frame_step_optional_route_kind_12(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}
asm(".align 2,0");
