#include "frame_actor_attachment_jobs_16_17.h"

unsigned int frame_step_attachment_job_16_2bccc(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    switch((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor,
            g_actor_reverse_directions[owner->object->unknown_12[0]]);
        frame_request_animation((struct FrameCommandObject *)job->actor,58);
        job->timer = 6;
        break;
    case 6:
        if(job->actor->flags & 0x400000) {
            job->timer = 1;
            resource_submit_scene(21,0,13);
        }
        break;
    }
    if(job->timer == 1) {
        frame_request_animation((struct FrameCommandObject *)job->actor,1);
        return 2;
    }
    return 1;
}
asm(".align 2,0");
