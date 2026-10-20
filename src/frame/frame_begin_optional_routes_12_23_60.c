#include "frame_optional_routes_12_23_60.h"

unsigned int frame_begin_optional_routes_12_23_60(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor,
                                                 unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(owner, actor);
    unsigned int result;
    if (!job) result = 0;
    else {
        job->kind = kind;
        frame_route_attachment_to_target(g_frame_registration, job, owner);
        result = 1;
    }
    return result;
}
asm(".align 2,0");
