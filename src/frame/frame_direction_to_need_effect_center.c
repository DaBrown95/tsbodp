#include "display_actor_interaction.h"
#include "view_math.h"
#include "frame_actor_target_jobs.h"

unsigned char frame_direction_to_need_effect_center(struct FrameObject *actor,
                                                      struct FrameNeedEffectState *owner)
{
    struct FramePoint first, second, position, delta, center;
    frame_grid_coordinates_to_point(g_frame_registration,
                                   &((struct FrameAttachmentEffectWork *)owner)->second, &first);
    frame_grid_coordinates_to_point(g_frame_registration,
                                   &((struct FrameAttachmentEffectWork *)owner)->first, &second);
    center.x = (first.x + second.x) / 2;
    center.y = (second.y + first.y) / 2;
    frame_point_to_integer(&actor->position, &position);
    delta.x = center.x - position.x;
    delta.y = center.y - position.y;
    return frame_direction_from_velocity(delta);
}
