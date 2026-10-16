#include "frame_actor_attachment_job_46.h"
unsigned int frame_step_attachment_job_46(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1) job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor, ((struct FrameActorObject *)owner->object)->direction);
        job->timer = 60;
        frame_request_animation((struct FrameCommandObject *)job->actor, 47);
        frame_commit_need_effect(owner->object, 3);
        ((struct FrameAttachmentJob46Work *)owner)->elapsed = 0;
        if (job->actor->id == 0) {
            ((struct FrameAttachmentJob46Work *)owner)->duration =
                frame_read_signed_parameter(g_frame_actor_social_probe, 3) * 50;
            ((struct FrameAttachmentJob46Work *)owner)->duration += frame_actor_need_value(needs, 2) * 2;
        } else {
            ((struct FrameAttachmentJob46Work *)owner)->duration = 240;
        }
        if (g_frame_interaction_settings.attachment_mode == 0) audio_play_animation_cue(146);
        else audio_play_animation_cue(140);
        ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(45);
        break;
    case 60:
        frame_adjust_actor_needs(needs, 19, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (++((struct FrameAttachmentJob46Work *)owner)->elapsed >=
                ((struct FrameAttachmentJob46Work *)owner)->duration)
            job->timer = 1;
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        frame_commit_need_effect(owner->object, 2);
        audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
        if (g_frame_interaction_settings.attachment_mode == 0) audio_play_animation_cue(141);
        else audio_play_animation_cue(140);
        if (((struct FrameAttachmentJob46Work *)owner)->elapsed > 479)
            resource_set_triple(3, 4, 1);
        result = 2;
        break;
    }
    return result;
}
