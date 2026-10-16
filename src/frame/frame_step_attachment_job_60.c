#include "frame_actor_attachment_jobs_60_63.h"
unsigned int frame_step_attachment_job_60(struct FrameNeedEffectState *owner,
                                           struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1) job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_request_animation((struct FrameCommandObject *)job->actor, 8);
        ((struct FrameActorStateWork *)job->actor)->timer = 60;
        job->timer = 30;
        if (g_frame_interaction_settings.attachment_mode == 0) audio_play_animation_cue(133);
        else audio_play_animation_cue(132);
        break;
    case 30:
        frame_adjust_attachment_need(needs, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned char)frame_step_attachment_need_timer(job, needs, 7,
                &((struct FrameActorStateWork *)job->actor)->timer) == 0)
            job->timer = 1;
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2,0");
