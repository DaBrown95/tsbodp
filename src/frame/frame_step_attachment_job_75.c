#include "frame_actor_attachment_job_75.h"
unsigned int frame_step_attachment_job_75(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        ((struct FrameActorObject *)job->actor)->direction =
            frame_direction_to_need_effect_center(job->actor, owner);
        job->timer = 83;
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        ((struct FrameActorStateWork *)job->actor)->timer = 90;
        break;
    case 83:
        if (job->actor->flags & 0x400000) {
            frame_adjust_actor_needs(needs, 11, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
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
