#include "frame_optional_routes_12_23_60.h"

unsigned int frame_step_optional_route_kind_23(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;
    if (job->running == 1) job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_need_effect_accumulate_optional(owner);
        frame_request_animation((struct FrameCommandObject *)job->actor, 45);
        job->timer = 33;
        ((struct FrameActorStateWork *)job->actor)->timer = 90;
        break;
    case 33:
        frame_adjust_actor_needs(needs, 54, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (--((struct FrameActorStateWork *)job->actor)->timer == -1)
            job->timer = 1;
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2,0");
