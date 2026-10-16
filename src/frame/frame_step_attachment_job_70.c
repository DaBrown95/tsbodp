#include "frame_actor_attachment_job_70.h"

unsigned int frame_step_attachment_job_70(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs =
        ((struct FrameActorObject *)job->actor)->actor_state;
    int previous;
    unsigned char percentage;
    switch ((unsigned int)job->timer) {
    case 0:
        previous = frame_read_signed_parameter(g_frame_actor_social_probe, 4);
        ((struct FrameAttachmentJobWork *)owner)->indicator = 0;
        if (previous != 10) {
            ((struct FrameAttachmentJobWork *)owner)->indicator =
                frame_create_attachment_parameter_indicator(job->actor, 1);
            ((struct FrameActorObject *)job->actor)->direction =
                frame_direction_to_need_effect_center(job->actor, owner);
        }
        frame_request_animation((struct FrameCommandObject *)job->actor, 34);
        job->timer = 81;
        ((struct FrameActorStateWork *)job->actor)->timer = 150;
        break;
    case 81:
        previous = frame_read_signed_parameter(g_frame_actor_social_probe, 4);
        if (previous != 10) {
            percentage = (unsigned char)frame_read_parameter_percentage(g_frame_actor_social_probe, 4);
            frame_set_attachment_parameter_indicator(
                ((struct FrameAttachmentJobWork *)owner)->indicator, percentage);
            frame_update_attachment_parameter(g_frame_actor_social_probe, 4,
                ((struct FrameAttachmentJobWork *)owner)->indicator);
            if (frame_read_signed_parameter(g_frame_actor_social_probe, 4) == previous + 1)
                job->timer = 1;
        } else {
            if (--((struct FrameActorStateWork *)job->actor)->timer == -1)
                job->timer = 1;
        }
        frame_adjust_actor_needs(needs, 47,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned char)frame_step_attachment_need_timer(job, needs, 6,
                &((struct FrameActorStateWork *)job->actor)->timer) == 0)
            job->timer = 1;
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        if (((struct FrameAttachmentJobWork *)owner)->indicator) {
            transition_object_set_state(((struct FrameAttachmentJobWork *)owner)->indicator, 1);
            ((struct FrameAttachmentJobWork *)owner)->indicator = 0;
        }
        return 2;
    }
    return 1;
}
asm(".align 2, 0");
