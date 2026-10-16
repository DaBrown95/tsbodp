#include "frame_actor_attachment_job_43.h"
unsigned int frame_step_attachment_job_43(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1) job->timer = 9;
    switch ((unsigned int)job->timer) {
    case 0:
        ((struct FrameActorObject *)job->actor)->direction =
            frame_direction_to_need_effect_center(job->actor, owner);
        job->timer = 6;
        if (frame_world_in_idle_exclusion_set(g_frame_world_id)) break;
        if (frame_gate_attachment_game_value(owner, job, 5)) break;
        frame_request_animation((struct FrameCommandObject *)job->actor, 5);
        if (g_frame_interaction_settings.attachment_mode == 0) audio_play_animation_cue(86);
        else audio_play_animation_cue(85);
        job->timer = 8;
        break;
    case 8:
        if (job->actor->flags & 0x400000) job->timer = 1;
        break;
    case 6:
        job->timer = 61;
        frame_request_animation((struct FrameCommandObject *)job->actor, 36);
        ((struct FrameActorStateWork *)job->actor)->timer = 150;
        frame_commit_need_effect(owner->object, 3);
        ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(67);
        break;
    case 61:
        frame_adjust_actor_needs(needs, 17, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned char)frame_step_attachment_need_timer(job, needs, 6,
                &((struct FrameActorStateWork *)job->actor)->timer) == 0)
            job->timer = 9;
        break;
    case 9:
        {
            struct FramePoint point;
            audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
            frame_attachment_position(owner->object, 1, &point);
            frame_request_animation((struct FrameCommandObject *)job->actor, 6);
            frame_begin_actor_route(job->actor, &point, &job->status, 3, 1);
            job->timer = 1;
            audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
        }
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
