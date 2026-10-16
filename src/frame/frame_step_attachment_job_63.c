#include "frame_actor_attachment_jobs_60_63.h"
unsigned int frame_step_attachment_job_63(struct FrameNeedEffectState *owner,
                                           struct FrameActorAttachmentRecord *job)
{
    switch ((unsigned int)job->timer) {
    case 0:
        owner->parameter = 0x100;
        ((struct FrameAttachmentRecoveryWork *)owner)->countdown = 3600;
        frame_request_animation((struct FrameCommandObject *)job->actor, 64);
        job->timer = 28;
        ((struct FrameActorStateWork *)job->actor)->timer = 0;
        break;
    case 28:
        {
            int count = ++((struct FrameActorStateWork *)job->actor)->timer;
            if (count == 22)
                ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(162);
            else if (count == 40)
                audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
            if (job->actor->flags & 0x400000) {
                frame_clear_animation_pending(job->actor);
                job->timer = 29;
                if (owner->object->unknown_0a == 19 && frame_random_range(0, 100) <= 32) {
                    unsigned char direction = ((struct FrameActorObject *)job->actor)->direction;
                    unsigned char reverse;
                    if (direction > 3) reverse = direction - 4;
                    else reverse = direction + 4;
                    if ((signed char)reverse == ((struct FrameActorObject *)owner->object)->direction) {
                        job->timer = 31;
                        frame_commit_need_effect(owner->object, 1);
                        ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(42);
                    }
                }
            }
        }
        break;
    case 31:
        if (owner->object->flags & 0x400000) {
            audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
            audio_play_animation_cue(207);
            frame_commit_need_effect(owner->object, 3);
            transition_object_set_state(g_need_effect_player, 47);
            frame_set_variant_state(g_need_effect_player, 73);
            job->actor->flags &= ~1u;
        }
        break;
    case 29:
        if (job->actor->flags & 0x400000) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
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
