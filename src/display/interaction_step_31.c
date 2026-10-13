#include "display_actor_interaction.h"

unsigned int frame_interaction_step_31(struct FrameNeedEffectState *owner,
                                       struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    struct FramePoint point;
    switch ((unsigned int)job->timer) {
    case 0:
        {
            unsigned char attachment = g_frame_interaction_settings.attachment_mode != 1;
            frame_attachment_position(owner->object, attachment, &point);
        }
        if (frame_begin_actor_route(job->actor, &point, &job->status, 4, 1) == 1)
            job->timer = 45;
        else
            job->timer = 1;
        break;
    case 45:
        ((struct FrameActorObject *)job->actor)->direction = ((struct FrameActorObject *)owner->object)->direction;
        job->timer = 41;
        frame_request_animation((struct FrameCommandObject *)job->actor, 50);
        *(int *)((unsigned char *)job->actor + 0x58) = 90;
        frame_commit_need_effect(owner->object, 1);
        break;
    case 41:
        if (job->actor->flags & 0x400000) {
            frame_clear_animation_pending(job->actor);
            audio_play_animation_cue(65);
            job->timer = 43;
        }
        break;
    case 43:
        frame_adjust_actor_needs(needs, 22, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (!frame_step_attachment_need_timer(job, needs, 4,
                                             (int *)((unsigned char *)job->actor + 0x58))) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 6);
            frame_attachment_position(owner->object, 2, &point);
            frame_begin_actor_route(job->actor, &point, &job->status, 4, 1);
        }
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        return 2;
    }
    return 1;
}
asm(".align 2, 0");
