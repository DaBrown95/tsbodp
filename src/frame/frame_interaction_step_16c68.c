#include "display_actor_interaction.h"
#include "frame_actor_finish.h"
#include "frame_need_effect_placement.h"
#include "frame_actor_target_routes.h"

unsigned int frame_interaction_step_16c68(struct FrameNeedEffectState *owner,
                                         struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
    struct FramePoint point;
    int cell;
    if (job->running == 1) job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 1:
        goto finish;
    case 0:
        ((struct FrameActorObject *)job->actor)->direction =
            ((struct FrameActorObject *)owner->object)->direction;
        job->timer = 41;
        frame_request_animation((struct FrameCommandObject *)job->actor, 50);
        *(int *)((unsigned char *)job->actor + 0x58) = 90;
        frame_commit_need_effect(owner->object, 1);
        if (((struct FrameActorObject *)owner->object)->direction == 3 ||
            ((struct FrameActorObject *)owner->object)->direction == 5)
            frame_need_effect_handoff_bounds(job->actor, owner, 1);
        else
            frame_need_effect_handoff_bounds(job->actor, owner, 0);
        break;
    case 41:
        if (job->actor->flags & 0x400000) {
            frame_clear_animation_pending(job->actor);
            job->timer = 43;
        }
        break;
    case 43:
        frame_adjust_actor_needs(needs, 22,
                                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (!(unsigned char)frame_step_attachment_need_timer(job, needs, 4,
                                                (int *)((unsigned char *)job->actor + 0x58)))
            job->timer = 1;
        break;
    }
    if (job->timer == 1) goto finish;
    return 1;
finish:
    frame_find_attachment_neighbor(g_frame_registration, owner->object,
                                  (unsigned int)job->actor, 0, &cell);
    frame_grid_cell_to_point(g_frame_registration, &cell, &point);
    job->actor->position.x = point.x << 16;
    job->actor->position.y = point.y << 16;
    frame_request_animation((struct FrameCommandObject *)job->actor, 1);
    frame_commit_need_effect(owner->object, 0);
    ((struct FrameActorFinishBounds *)job->actor)->before_step = resource_object_before_step;
    return 2;
}
