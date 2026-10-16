#include "frame_actor_attachment_job_26.h"

unsigned int frame_step_attachment_job_26(struct FrameNeedEffectState *owner,
                                        struct FrameActorAttachmentRecord *job)
{
    if (!job->running) {
        switch ((unsigned int)job->timer) {
        case 0:
            frame_request_animation((struct FrameCommandObject *)job->actor, 60);
            job->timer = 6;
            ((struct FrameActorStateWork *)job->actor)->timer = 30;
            break;
        case 6:
            if (--((struct FrameActorStateWork *)job->actor)->timer == -1) {
                job->timer = 1;
                frame_refresh_random_seed();
                scene_submit_default_request(9);
            }
            break;
        }
    } else
        job->timer = 1;
    if (job->timer == 1)
        return 2;
    return 1;
}
