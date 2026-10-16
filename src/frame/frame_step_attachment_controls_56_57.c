#include "frame_actor_attachment_control_jobs.h"

unsigned int frame_step_attachment_controls_56_57(struct FrameNeedEffectState *owner,
                                                 struct FrameActorAttachmentRecord *job,
                                                 unsigned int mode)
{
    switch ((unsigned int)job->timer) {
    case 0:
        if (!mode)
            owner->parameter = 0xa00;
        else
            owner->parameter = 0;
        frame_set_actor_direction(job->actor,
            ((struct FrameActorObject *)owner->object)->direction);
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        job->timer = 6;
        break;
    case 6:
        if (job->actor->flags & 0x400000) {
            if ((short)owner->parameter != 0)
                frame_commit_need_effect(owner->object, 3);
            else
                frame_commit_need_effect(owner->object, 0);
            job->timer = 1;
        }
        break;
    }
    if (job->timer == 1) {
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        return 2;
    }
    return 1;
}
asm(".align 2,0");
