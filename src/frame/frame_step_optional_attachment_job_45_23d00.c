#include "frame_actor_attachment_jobs_45_56_57.h"

unsigned int frame_step_optional_attachment_job_45_23d00(struct FrameNeedEffectState *owner,
                                                        struct FrameActorAttachmentRecord *job)
{
    if (!job->running) {
        switch ((unsigned int)job->timer) {
        case 0:
            if (frame_need_effect_try_actor_effect(owner, job->actor) == 1) {
                job->timer = 1;
            } else {
                ((struct FrameAttachmentJobWork *)owner)->indicator =
                    frame_create_attachment_parameter_indicator(job->actor, 0);
                frame_request_animation((struct FrameCommandObject *)job->actor, 46);
                job->timer = 5;
                ((struct FrameAttachmentJobWork *)owner)->sample =
                    audio_play_animation_cue(19);
            }
            break;
        case 5:
            if ((unsigned char)frame_need_effect_consume_optional(owner, job,
                    ((struct FrameAttachmentJobWork *)owner)->indicator) == 1)
                job->timer = 1;
            break;
        }
    } else {
        job->timer = 1;
    }
    if (job->timer == 1) {
        audio_game_stop_sample(((struct FrameAttachmentJobWork *)owner)->sample);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        if (((struct FrameAttachmentJobWork *)owner)->indicator) {
            transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator, 1);
            ((struct FrameAttachmentJobWork *)owner)->indicator = 0;
        }
        return 2;
    }
    return 1;
}
