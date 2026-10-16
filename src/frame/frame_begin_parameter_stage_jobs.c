#include "frame_parameter_stage_jobs.h"

unsigned int frame_begin_parameter_stage_jobs(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    unsigned int result;
    if (!job)
        result = 0;
    else {
        job->kind = kind;
        frame_route_attachment_to_target(g_frame_registration, job, owner);
        result = 1;
    }
    return result;
}
