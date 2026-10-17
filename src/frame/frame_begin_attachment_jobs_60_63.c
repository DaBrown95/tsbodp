#include "frame_actor_attachment_jobs_60_63.h"
unsigned int frame_begin_attachment_jobs_60_63(struct FrameNeedEffectState *owner,
                                               struct FrameObject *actor,
                                               unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        owner, actor);
    unsigned int result;
    if (job == 0) result = 0;
    else {
        job->kind = kind;
        frame_route_attachment_to_target(g_frame_registration, job, owner);
        result = 1;
    }
    return result;
}
