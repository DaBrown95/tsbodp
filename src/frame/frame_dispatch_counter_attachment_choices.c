#include "frame_actor_attachment_counter_choices.h"

unsigned int frame_dispatch_counter_attachment_choices(struct FrameNeedEffectState *owner,
                                                        struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner,actor);
    unsigned int result;
    switch (job->kind) {
    case 19:
        result = frame_step_counter_attachment_job_19(owner,job);
        break;
    case 68:
        result = frame_step_counter_attachment_jobs_68_69(owner,job);
        break;
    case 69:
        result = frame_step_counter_attachment_jobs_68_69(owner,job);
        break;
    case 20:
        result = 2;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}
