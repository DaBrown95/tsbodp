#include "frame_actor_attachment_timed_job_12.h"

unsigned int frame_step_timed_attachment_job_12(struct FrameNeedEffectState *owner,
                                                struct FrameActorAttachmentRecord *job)
{
    switch ((unsigned int)job->timer) {
    case 0:
        frame_stop_motion(job->actor);
        job->timer = 48;
        frame_set_actor_direction(job->actor,2);
        frame_request_animation((struct FrameCommandObject *)job->actor,27);
        ((struct FrameActorStateWork *)job->actor)->timer = 120;
        break;
    case 48:
        frame_adjust_actor_needs(((struct FrameActorObject *)job->actor)->actor_state,
            52,g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorStateWork *)job->actor)->timer == -1) {
            transition_object_set_state(owner->object,1);
            frame_request_animation((struct FrameCommandObject *)job->actor,1);
            job->timer = 1;
        }
        break;
    }
    if (job->timer == 1) return 2;
    return 1;
}
