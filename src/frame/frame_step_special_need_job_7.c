#include "frame_special_need_jobs.h"

unsigned int frame_step_special_need_job_7(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor, 0);
        frame_request_animation((struct FrameCommandObject *)job->actor, 8);
        job->timer = 3;
        ((struct FrameActorSocialWork *)job->actor)->timer = 90;
        if (g_frame_interaction_settings.attachment_mode == 0)
            audio_play_animation_cue(133);
        else
            audio_play_animation_cue(132);
        break;
    case 3:
        frame_adjust_attachment_need(needs,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorSocialWork *)job->actor)->timer == -1) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        }
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2,0");
