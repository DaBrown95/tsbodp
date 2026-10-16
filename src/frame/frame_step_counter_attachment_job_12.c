#include "frame_actor_counter_attachment_job_12.h"

unsigned int frame_step_counter_attachment_job_12(struct FrameNeedEffectState *owner,
                                                  struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        job->timer = 48;
        frame_request_animation((struct FrameCommandObject *)job->actor, 27);
        ((struct FrameActorStateWork *)job->actor)->timer = 150;
        break;
    case 48:
        frame_adjust_actor_needs(((struct FrameActorObject *)job->actor)->actor_state, 52,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorStateWork *)job->actor)->timer == -1) {
            transition_object_set_state(owner->object, 1);
            job->timer = 1;
        }
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2, 0");
