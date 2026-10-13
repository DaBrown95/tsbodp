#include "frame_need_effect_optional_jobs.h"

unsigned int frame_step_optional_animation_attachment_job(struct FrameNeedEffectState *owner,
                                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_need_effect_try_optional(owner);
        frame_set_actor_direction(job->actor, g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        job->timer = 6;
        audio_play_animation_cue(175);
        break;
    case 6:
        if (job->actor->flags & 0x400000) {
            ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(61);
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
            ((struct FrameActorStateWork *)job->actor)->timer = 90;
            job->timer = 55;
        }
        break;
    case 55:
        if (--((struct FrameActorStateWork *)job->actor)->timer == -1) {
            audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
            job->timer = 56;
            frame_request_animation((struct FrameCommandObject *)job->actor, 21);
            ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(21);
        }
        break;
    case 56:
        frame_adjust_actor_needs(needs, 4, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (job->actor->flags & 0x400000) {
            audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        }
        break;
    }
    if (job->running == 1)
        job->timer = 1;
    if (job->timer == 1) {
        audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
        if (!g_frame_interaction_settings.attachment_mode)
            audio_play_animation_cue(146);
        else
            audio_play_animation_cue(145);
        return 2;
    }
    return 1;
}
asm(".align 2, 0");
