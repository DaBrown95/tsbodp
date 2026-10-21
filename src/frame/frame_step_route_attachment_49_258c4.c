#include "frame_route_attachment_49.h"
#include "display_actor_interaction.h"

unsigned int frame_step_route_attachment_49_258c4(struct FrameNeedEffectState *owner,
    struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs =
        ((struct FrameActorObject *)job->actor)->actor_state;

    switch ((unsigned int)job->timer) {
    case 0:
        ((struct FrameActorObject *)job->actor)->direction =
            ((struct FrameActorObject *)owner->object)->direction;
        job->timer = 41;
        frame_request_animation((struct FrameCommandObject *)job->actor, 50);
        *(int *)((unsigned char *)job->actor + 0x58) = 150;
        break;
    case 41:
        if (job->actor->flags & 0x400000) {
            frame_clear_animation_pending(job->actor);
            job->timer = 43;
        }
        break;
    case 43:
        frame_adjust_actor_needs(needs, 24,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (!(unsigned char)frame_step_attachment_need_timer(job, needs, 4,
                (int *)((unsigned char *)job->actor + 0x58))) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        }
        break;
    }
    if (job->timer == 1)
        return 2;
    return 1;
}
