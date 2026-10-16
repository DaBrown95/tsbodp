#include "frame_actor_attachment_control_jobs.h"

unsigned int frame_step_attachment_job_100_171c8(struct FrameNeedEffectState *owner,
                                                struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs =
        ((struct FrameActorObject *)job->actor)->actor_state;

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
            frame_set_actor_direction(job->actor,
                ((struct FrameActorObject *)owner->object)->direction);
            job->timer = 20;
            frame_request_animation((struct FrameCommandObject *)job->actor, 59);
            ((struct FrameActorStateWork *)job->actor)->timer = 150;
            ((struct FrameAttachmentJobWork *)owner)->sample =
                audio_play_animation_cue(17);
        }
        break;
    case 20:
        if ((((struct FrameActorStateWork *)job->actor)->timer & 31) == 0) {
            audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
            if (frame_random_range(0, 2) == 0)
                ((struct FrameAttachmentJobWork *)owner)->sample =
                    audio_play_animation_cue(27);
            else
                ((struct FrameAttachmentJobWork *)owner)->sample =
                    audio_play_animation_cue(17);
        }
        frame_adjust_actor_needs(needs, 2,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned char)frame_step_attachment_need_timer(job, needs, 6,
                &((struct FrameActorStateWork *)job->actor)->timer) == 0) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        }
        break;
    case 8:
        if (job->actor->flags & 0x400000) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
            frame_clear_attachment_need_countdown(needs);
        }
        break;
    }
    if (job->timer == 1) {
        audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
        return 2;
    }
    return 1;
}
asm(".align 2,0");
