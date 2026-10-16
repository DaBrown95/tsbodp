#include "frame_actor_attachment_jobs_3_4_18.h"

unsigned int frame_step_attachment_sequence_jobs_3_4(struct FrameNeedEffectState *owner,
                                                     struct FrameActorAttachmentRecord *job,
                                                     unsigned int enabled)
{
    struct FrameAttachmentSequenceMode *work = (struct FrameAttachmentSequenceMode *)owner;
    switch ((unsigned int)job->timer) {
    case 0:
        work->enabled = enabled;
        frame_set_actor_direction(job->actor, 1);
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
