#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_direct_move.h"

void frame_unrooted_actor_waypoint_step_82bc(struct FrameObject *object)
{
    struct FramePoint tile, point;

    switch (((struct FrameActorObject *)object)->variant_state) {
    case 0:
        ((struct FrameActorStateWork *)object)->waypoint_index =
            frame_random_range(0, resource_group_point_count(
                ((struct FrameActorStateWork *)object)->waypoint_group) - 1);
        tile = resource_read_group_point(
            ((struct FrameActorStateWork *)object)->waypoint_group,
            ((struct FrameActorStateWork *)object)->waypoint_index);
        point = tile;
        frame_set_actor_destination(object, &point);
        frame_set_variant_state(object, 3);
        break;
    case 3:
        if (frame_actor_face_destination(object)) {
            frame_actor_choose_next_waypoint(object);
            frame_set_variant_state(object, 7);
            ((struct FrameActorStateWork *)object)->timer =
                ((struct FrameActorStateWork *)object)->wait_units * 30;
        }
        break;
    case 2:
        frame_actor_choose_next_waypoint(object);
        frame_actor_face_destination(object);
        frame_set_variant_state(object, 3);
        break;
    default:
        frame_actor_step_wait_phase(object);
        break;
    }
}

/* Native zero-filled alignment after the returned instruction body. */
asm(".align 2, 0");
