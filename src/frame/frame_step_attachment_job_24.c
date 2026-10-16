#include "frame_actor_attachment_job_24.h"

unsigned int frame_step_attachment_job_24(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs =
        ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        if (frame_attachment_need_is_low(needs, 6) == 1) {
            frame_set_actor_direction(job->actor, 4);
            frame_request_animation((struct FrameCommandObject *)job->actor, 85);
            if (g_frame_interaction_settings.attachment_mode == 0)
                audio_play_animation_cue(137);
            else
                audio_play_animation_cue(136);
            job->timer = 8;
        } else {
            job->timer = 13;
            frame_request_animation((struct FrameCommandObject *)job->actor, 17);
            frame_commit_need_effect(owner->object, 3);
            ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(41);
            ((struct FrameActorStateWork *)job->actor)->timer = 150;
        }
        break;
    case 13:
        frame_adjust_actor_needs(needs, 10,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned char)frame_step_attachment_need_timer(job, needs, 6,
                &((struct FrameActorStateWork *)job->actor)->timer) == 0)
            job->timer = 1;
        break;
    case 8:
        if (job->actor->flags & 0x400000) {
            job->timer = 1;
            frame_clear_attachment_need_countdown(needs);
        }
        break;
    case 1:
        audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        frame_commit_need_effect(owner->object, 2);
        result = 2;
        break;
    }
    return result;
}
