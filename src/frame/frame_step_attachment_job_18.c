#include "frame_actor_attachment_job_18.h"

unsigned int frame_step_attachment_job_18(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs =
        ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor,
            frame_direction_to_need_effect_center(job->actor, owner));
        if (frame_random_chance(50) == 1)
            frame_request_animation((struct FrameCommandObject *)job->actor, 20);
        else
            frame_request_animation((struct FrameCommandObject *)job->actor, 19);
        job->timer = 20;
        ((struct FrameActorStateWork *)job->actor)->timer = 300;
        break;
    case 20:
        if (frame_need_effect_attachment_count(owner) == 1)
            frame_adjust_actor_needs(needs, 2,
                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        else
            frame_adjust_actor_needs(needs, 3,
                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned char)frame_step_attachment_need_timer(job, needs, 6,
                &((struct FrameActorStateWork *)job->actor)->timer) == 0) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
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
