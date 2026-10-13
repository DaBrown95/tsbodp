#include "display_actor_interaction.h"
#include "frame_actor_choices.h"
#include "frame_actor_target_routes.h"

void frame_route_attachment_to_target(void *context,
                                     struct FrameActorAttachmentRecord *job,
                                     struct FrameNeedEffectState *owner)
{
    struct FramePoint point;
    int cell;
    frame_point_to_integer(&job->actor->position, &point);
    frame_grid_point_to_cell(context, &point, (struct FrameActorPackedCell *)&cell);
    if (frame_find_target_cell(context, job->actor, owner->object, &cell, 1)) {
        frame_grid_cell_to_point(context, &cell, &point);
        frame_point_to_fixed(&point, &point);
        frame_begin_actor_route(job->actor, &point, &job->status, 4, 1);
        frame_request_animation((struct FrameCommandObject *)job->actor, 6);
    }
}
