#include "frame_route_attachment_21_45.h"

unsigned int frame_step_route_attachment_21_12a04(struct FrameNeedEffectState *owner,
                                                        struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_need_effect_try_optional(owner);
        frame_set_actor_direction(job->actor,
            g_actor_reverse_directions[((struct FrameActorObject *)owner->object)->direction]);
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        job->timer = 75;
        break;
    case 75:
        if (job->actor->flags & 0x400000) {
            frame_request_animation((struct FrameCommandObject *)job->actor, 32);
            frame_commit_need_effect(owner->object, 1);
            job->timer = 76;
            ((struct FrameActorObject *)job->actor)->need_timer = 60;
        }
        break;
    case 76:
        if (job->actor->flags & 0x400000)
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        if (--((struct FrameActorObject *)job->actor)->need_timer == 0xffff) {
            frame_commit_need_effect(owner->object, 2);
            job->timer = 77;
            ((struct FrameActorObject *)job->actor)->need_timer = 60;
            frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        }
        break;
    case 77:
        if (job->actor->flags & 0x400000) {
            frame_commit_need_effect(owner->object, 2);
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
