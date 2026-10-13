#include "frame_need_effect_optional_activity.h"
#include "display_need_effect_update.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"

static inline void failed_begin(struct FrameActorAttachmentRecord *job)
{
    frame_request_animation((struct FrameCommandObject *)job->actor, 5);
    if (g_frame_interaction_settings.attachment_mode == 0)
        audio_play_animation_cue(86);
    else
        audio_play_animation_cue(85);
    job->timer = 8;
}

unsigned int frame_step_optional_activity_attachment_job(struct FrameNeedEffectState *owner,
                                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor, g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
        job->timer = 6;
        if (condition_is_complete(0, 4, 0)) {
            switch (job->kind) {
            case 28: case 30: case 32:
                if (frame_gate_attachment_game_value(owner, job, g_frame_world_id == 28 ? 40 : 20) == 1) {
                    frame_need_effect_try_optional(owner);
                    frame_need_effect_accumulate_optional(owner);
                } else
                    failed_begin(job);
                break;
            case 31: case 33:
                if (!frame_gate_attachment_game_value(owner, job, g_frame_world_id == 28 ? 20 : 10))
                    failed_begin(job);
                break;
            }
        }
        break;
    case 8:
        if (job->actor->flags & 0x400000)
            job->timer = 1;
        break;
    case 6:
        frame_request_animation((struct FrameCommandObject *)job->actor, 61);
        frame_commit_need_effect(owner->object, 3);
        audio_play_animation_cue(166);
        job->timer = 54;
        ((struct FrameActorObject *)job->actor)->need_timer = 300;
        break;
    case 54:
        if ((((struct FrameActorObject *)job->actor)->need_timer & 31) == 0)
            audio_play_animation_cue(22);
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535) {
            if (!frame_need_effect_try_reset_timer(owner, job->actor)) {
                job->timer = 25;
                ((struct FrameActorObject *)job->actor)->need_timer = 150;
                frame_request_animation((struct FrameCommandObject *)job->actor, 23);
                ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(20);
                frame_commit_need_effect(owner->object, 0);
            } else {
                frame_need_effect_begin_optional_three(owner);
                job->timer = 9;
            }
        }
        break;
    case 25:
        frame_adjust_actor_needs(needs, 7, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535) {
            job->timer = 9;
            resource_set_triple(0, 1, 0);
        }
        break;
    case 10:
        if (job->actor->flags & 0x400000)
            result = 2;
        break;
    case 9:
        job->timer = 1;
        break;
    case 1:
        audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
        frame_commit_need_effect(owner->object, 0);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2, 0");
