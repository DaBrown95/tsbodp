#include "frame_actor_attachment_sequence_jobs.h"
unsigned int frame_step_attachment_sequence_modes_2_5(struct FrameNeedEffectState *owner,
                                                     struct FrameActorAttachmentRecord *job,
                                                     unsigned int mode)
{
    switch ((unsigned int)job->timer) {
    case 0:
        if (mode == 0)
            owner->parameter = 0xa00;
        else
            owner->parameter = 0xb00;
        frame_set_actor_direction(job->actor, g_actor_reverse_directions[
            ((struct FrameActorObject *)owner->object)->direction]);
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        job->timer = 6;
        break;
    case 6:
        if (job->actor->flags & 0x400000)
            job->timer = 1;
        break;
    }
    if (job->timer == 1) {
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        return 2;
    }
    return 1;
}
asm(".align 2,0");
