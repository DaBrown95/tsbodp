#include "frame_actor_attachment_control_jobs.h"

unsigned int frame_dispatch_attachment_control_jobs(struct FrameNeedEffectState *owner,
                                                    struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    unsigned int result;

    switch (job->kind) {
    case 57:
        result = frame_step_attachment_controls_56_57(owner, job, 0);
        frame_refresh_attachment_control_174a8(owner);
        break;
    case 56:
        result = frame_step_attachment_controls_56_57(owner, job, 1);
        audio_select_sequence(scene_audio_for_period(g_scene_context.period));
        g_audio_control.flags |= 8;
        break;
    case 98:
        result = frame_step_attachment_controls_98_99_101(owner, job, 2);
        frame_refresh_attachment_control_174a8(owner);
        break;
    case 99:
        result = frame_step_attachment_controls_98_99_101(owner, job, 3);
        frame_refresh_attachment_control_174a8(owner);
        break;
    case 101:
        result = frame_step_attachment_controls_98_99_101(owner, job, 4);
        frame_refresh_attachment_control_174a8(owner);
        break;
    case 100:
        result = frame_step_attachment_job_100_171c8(owner, job);
        break;
    case 45:
        result = frame_step_attachment_job_45_17124(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}

/* Zero alignment before the independently called next Thumb entry. */
asm(".align 2,0");
