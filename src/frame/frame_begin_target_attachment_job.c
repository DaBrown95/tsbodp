#include "display_actor_interaction.h"
#include "frame_actor_target_jobs.h"

unsigned int frame_begin_target_attachment_job(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor,
                                                 unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        owner, actor);
    unsigned char result;
    if (!job) result = 0;
    else {
        job->kind = kind;
        frame_route_attachment_to_target(g_frame_registration, job, owner);
        frame_request_animation((struct FrameCommandObject *)actor, 6);
        result = 1;
    }
    return result;
}
