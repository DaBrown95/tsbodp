#include "frame_actor_attachment_jobs_79_80.h"

unsigned int frame_step_attachment_jobs_79_80(struct FrameNeedEffectState *owner,
                                             struct FrameActorAttachmentRecord *job,
                                             unsigned char update_parameter)
{
    unsigned char percentage;
    int previous = 0;
    struct FrameActorNeedState *needs =
        ((struct FrameActorObject *)job->actor)->actor_state;

    switch ((unsigned int)job->timer) {
    case 0:
        frame_need_effect_try_optional(owner);
        if (update_parameter == 1)
            ((struct FrameAttachmentJobWork *)owner)->indicator =
                frame_create_attachment_parameter_indicator(job->actor, 1);
        job->actor->unknown_12[0] =
            frame_direction_to_need_effect_center(job->actor, owner);
        audio_play_animation_cue(178);
        frame_commit_need_effect(owner->object, 1);
        frame_request_animation((struct FrameCommandObject *)job->actor, 60);
        job->actor->motion_storage.motion.timer = 30;
        job->timer = 6;
        break;
    case 6:
        if (--job->actor->motion_storage.motion.timer == 0xffff) {
            frame_commit_need_effect(owner->object, 3);
            job->timer = 84;
            job->actor->motion_storage.motion.timer = 20;
        }
        break;
    case 84:
        if (update_parameter == 1) {
            previous = frame_read_signed_parameter(g_frame_actor_social_probe, 4);
            percentage = (unsigned char)frame_read_parameter_percentage(g_frame_actor_social_probe, 4);
            frame_set_attachment_parameter_indicator(
                ((struct FrameAttachmentJobWork *)owner)->indicator, percentage);
            frame_update_attachment_parameter(g_frame_actor_social_probe, 4,
                ((struct FrameAttachmentJobWork *)owner)->indicator);
        } else {
            frame_adjust_actor_needs(needs, 49,
                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
            if (--job->actor->motion_storage.motion.timer == 0xffff) {
                job->actor->motion_storage.motion.timer = frame_random_secondary_range(8, 30);
                ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(
                    g_frame_attachment_jobs_79_80_cues[frame_random_secondary_range(0, 5)]);
            }
        }
        if (update_parameter == 1 &&
            frame_read_signed_parameter(g_frame_actor_social_probe, 4) == previous + 1)
            job->timer = 1;
        if ((unsigned char)frame_step_attachment_need_timer(job, needs, 6,
                &((struct FrameActorStateWork *)job->actor)->timer) == 0)
            job->timer = 1;
        break;
    case 1:
        audio_play_animation_cue(178);
        frame_commit_need_effect(owner->object, 2);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        if (update_parameter == 1 && ((struct FrameAttachmentJobWork *)owner)->indicator) {
            transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator, 1);
            ((struct FrameAttachmentJobWork *)owner)->indicator = 0;
        }
        return 2;
    }
    return 1;
}
