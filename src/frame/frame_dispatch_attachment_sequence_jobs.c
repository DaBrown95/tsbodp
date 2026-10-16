#include "frame_actor_attachment_sequence_jobs.h"
unsigned int frame_dispatch_attachment_sequence_jobs(struct FrameNeedEffectState *owner,
                                                     struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        (struct FrameActorAttachmentOwner *)owner, actor);
    unsigned int result;
    switch (job->kind) {
    case 57:
        result = frame_step_attachment_sequence_modes_56_57(owner, job, 0);
        frame_refresh_attachment_sequence_41c18(owner);
        break;
    case 56:
        result = frame_step_attachment_sequence_modes_56_57(owner, job, 1);
        audio_select_sequence(scene_audio_for_period(g_scene_context.period));
        g_audio_control.flags |= 8;
        break;
    case 5:
        result = frame_step_attachment_sequence_modes_2_5(owner, job, 0);
        frame_refresh_attachment_sequence_41c18(owner);
        break;
    case 2:
        result = frame_step_attachment_sequence_modes_2_5(owner, job, 1);
        frame_refresh_attachment_sequence_41c18(owner);
        break;
    case 18:
        result = frame_step_attachment_sequence_job_18_41840(owner, job);
        break;
    case 45:
        result = frame_step_attachment_sequence_job_45_41794(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}
asm(".align 2,0");
