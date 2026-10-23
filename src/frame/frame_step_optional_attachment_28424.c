#include "frame_optional_attachment_dispatch.h"
#include "frame_need_effect_optional_activity.h"
#include "display_need_effect_update.h"
#include "resource_conditions.h"

static inline void failed_begin(struct FrameActorAttachmentRecord *job)
{
    frame_request_animation((struct FrameCommandObject *)job->actor, 5);
    if (g_frame_interaction_settings.attachment_mode == 0)
        audio_play_animation_cue(86);
    else
        audio_play_animation_cue(85);
    job->timer = 8;
}

unsigned int frame_step_optional_attachment_28424(struct FrameNeedEffectState *owner,
                                                 struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    unsigned int adjustment, amount;
    /* The shared need-adjustment call consumes this short R0 argument. */
    register struct FrameActorNeedState *argument_needs asm("r0");
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0: {
        /* This call phase carries the owner in callee-saved R6. Other phases
         * keep the ordinary owner value for their field accesses. */
        register struct FrameNeedEffectState *active_owner asm("r6") = owner;
        job->timer = 6;
        if ((unsigned char)condition_is_complete(0, 4, 0)) {
            switch (job->kind) {
            case 28: case 30: case 32:
                if (frame_gate_attachment_game_value(active_owner, job, 20) == 1) {
                    frame_need_effect_try_optional(active_owner);
                    frame_need_effect_accumulate_optional(active_owner);
                } else
                    failed_begin(job);
                break;
            case 31: case 33:
                if (frame_gate_attachment_game_value(active_owner, job, 10) == 1) {
                    frame_need_effect_try_optional(active_owner);
                    frame_need_effect_accumulate_optional(active_owner);
                } else
                    failed_begin(job);
                break;
            }
        }
        break;
    }
    case 8:
        if (job->actor->flags & 0x400000)
            job->timer = 1;
        break;
    case 6:
        frame_commit_need_effect(owner->object, 1);
        ((struct FrameActorObject *)owner->object)->pending_updates |= 4;
        ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(172);
        ((struct FrameActorObject *)job->actor)->need_timer = 150;
        job->timer = 49;
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        break;
    case 49:
        if (--((struct FrameActorObject *)job->actor)->need_timer == 65535) {
            /* The same sample-field address spans the stop, cue, commit and
             * animation calls, then receives the new sample handle. */
            register unsigned int *sample_slot asm("r4") = &((struct FrameAttachmentJobWork *)owner)->sample;
            audio_game_stop_sample(*sample_slot);
            audio_play_animation_cue(173);
            frame_commit_need_effect(owner->object, 0);
            switch (job->kind) {
            case 28: case 30: case 32:
                ((struct FrameActorObject *)job->actor)->need_timer = 150;
                job->timer = 25;
                break;
            case 31: case 33:
                ((struct FrameActorObject *)job->actor)->need_timer = 60;
                job->timer = 26;
                break;
            }
            frame_request_animation((struct FrameCommandObject *)job->actor, 23);
            *sample_slot = audio_play_animation_cue(20);
        }
        break;
    case 25:
        amount = g_frame_need_effect_definitions[owner->kind].unknown_04[31];
        argument_needs = needs;
        adjustment = 7;
        goto adjust_needs;
    case 26:
        amount = g_frame_need_effect_definitions[owner->kind].unknown_04[31];
        argument_needs = needs;
        adjustment = 8;
    adjust_needs:
        frame_adjust_actor_needs(argument_needs, adjustment, amount);
        if (job->running == 1 || --((struct FrameActorObject *)job->actor)->need_timer == 65535)
            job->timer = 9;
        break;
    case 9:
        frame_set_actor_direction(job->actor, 4);
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
