#include "frame_actor_attachment_jobs_3_4_18.h"

unsigned int frame_dispatch_attachment_jobs_3_4_18(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;
    switch (job->kind) {
    case 3:
        result = frame_step_attachment_sequence_jobs_3_4(owner, job, 1);
        audio_select_sequence(3);
        g_audio_control.flags |= 8;
        break;
    case 4:
        result = frame_step_attachment_sequence_jobs_3_4(owner, job, 0);
        audio_select_sequence(4);
        g_audio_control.flags |= 8;
        break;
    case 18:
        result = frame_step_attachment_job_18_23aa0(owner, job);
        break;
    default:
        result = 0;
        break;
    }
    return result;
}
