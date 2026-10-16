#include "frame_actor_attachment_jobs_13_14.h"

unsigned int frame_step_attachment_jobs_13_14(struct FrameNeedEffectState *owner,
                                             struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs =
        ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1) {
        job->timer = 1;
        audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
    }
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor, g_actor_reverse_directions[
            ((struct FrameActorObject *)owner->object)->direction]);
        job->timer = 6;
        if ((unsigned char)frame_gate_attachment_game_value(owner, job, 20))
            break;
        frame_request_animation((struct FrameCommandObject *)job->actor, 5);
        if (g_frame_interaction_settings.attachment_mode == 0)
            audio_play_animation_cue(86);
        else
            audio_play_animation_cue(85);
        job->timer = 8;
        break;
    case 8:
        if (job->actor->flags & 0x400000)
            job->timer = 1;
        break;
    case 6:
        frame_request_animation((struct FrameCommandObject *)job->actor, 59);
        if (job->kind == 13)
            frame_commit_need_effect(owner->object, 3);
        else
            frame_commit_need_effect(owner->object, 1);
        ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(174);
        job->timer = 54;
        ((struct FrameActorObject *)job->actor)->need_timer = 300;
        break;
    case 54:
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535) {
            job->timer = 25;
            ((struct FrameActorObject *)job->actor)->need_timer = 150;
            frame_request_animation((struct FrameCommandObject *)job->actor, 23);
            audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
            ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(20);
        }
        break;
    case 25:
        frame_adjust_actor_needs(needs, 7,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535)
            job->timer = 9;
        break;
    case 9:
        audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
        job->timer = 1;
        break;
    case 1:
        frame_commit_need_effect(owner->object, 0);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2,0");
