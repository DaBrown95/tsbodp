#include "display_actor_interaction.h"
#include "audio_game.h"
#include "frame_actor_target_jobs.h"

unsigned int frame_step_attachment_job_7(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1) job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor, frame_direction_to_need_effect_center(job->actor, owner));
        frame_request_animation((struct FrameCommandObject *)job->actor, 8);
        job->timer = 3;
        ((struct FrameActorObject *)job->actor)->need_timer = 150;
        if (owner->kind == 29 || owner->kind == 22) {
            frame_commit_need_effect(owner->object, 1);
            if (owner->kind == 29) audio_play_animation_cue(53);
            else audio_play_animation_cue(47);
        }
        if (g_frame_interaction_settings.attachment_mode == 0) audio_play_animation_cue(133);
        else audio_play_animation_cue(132);
        if (owner->kind == 20)
            ((struct FrameAttachmentEffectWork *)owner)->sample = audio_play_animation_cue(43);
        if (owner->kind == 25)
            ((struct FrameAttachmentEffectWork *)owner)->sample = audio_play_animation_cue(62);
        break;
    case 3:
        frame_adjust_attachment_need(needs, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535) job->timer = 1;
        break;
    case 1:
        if (owner->kind == 29 || owner->kind == 22) frame_commit_need_effect(owner->object, 2);
        if (owner->kind == 20 || owner->kind == 25)
            audio_game_stop_sample(((struct FrameAttachmentEffectWork *)owner)->sample);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
