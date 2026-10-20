#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_direct_move.h"

void frame_actor_choose_next_waypoint(struct FrameObject *object)
{
    unsigned char index;
    struct FramePoint tile, point;

    do {
        index = frame_random_range(0, resource_group_point_count(
            ((struct FrameActorStateWork *)object)->waypoint_group) - 1);
    } while (index == ((struct FrameActorStateWork *)object)->waypoint_index);
    ((struct FrameActorStateWork *)object)->waypoint_index = index;
    tile = resource_read_group_point(
        ((struct FrameActorStateWork *)object)->waypoint_group, index);
    point = tile;
    frame_set_actor_destination(object, &point);
}
