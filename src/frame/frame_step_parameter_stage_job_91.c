#include "frame_parameter_stage_jobs.h"

unsigned int frame_step_parameter_stage_job_91(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_request_animation((struct FrameCommandObject *)job->actor, 46);
        ((struct FrameActorObject *)job->actor)->need_timer = 90;
        job->timer = 90;
        if (g_frame_interaction_settings.attachment_mode == 0)
            audio_play_animation_cue(98);
        else
            audio_play_animation_cue(97);
        break;
    case 90:
        frame_adjust_actor_needs(needs, 36,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535) {
            if ((unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe, 2) <= 1) {
                owner->parameter = 0;
                job->timer = 1;
            } else {
                frame_commit_need_effect(owner->object, 1);
                owner->parameter = 0x1900;
                ((struct FrameActorObject *)job->actor)->need_timer = 90;
                job->timer = 91;
            }
        }
        break;
    case 91:
        frame_adjust_actor_needs(needs, 36,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535) {
            if (frame_read_signed_parameter(g_frame_actor_social_probe, 2) == 2)
                job->timer = 1;
            else {
                ((struct FrameActorObject *)job->actor)->need_timer = 90;
                job->timer = 92;
            }
            frame_commit_need_effect(owner->object, 3);
            owner->parameter = 0x3200;
        }
        break;
    case 92:
        frame_adjust_actor_needs(needs, 36,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535 &&
            (unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe, 2) > 2) {
            frame_commit_need_effect(owner->object, 2);
            owner->parameter = 0x6400;
            job->timer = 1;
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
