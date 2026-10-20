#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_direct_move.h"

/* Independently bounded entry; incoming roots and unused formals are unknown. */
void frame_unrooted_start_destination_move_8cd4(struct FrameObject *object,
                                              int x, int y, int speed)
{
    object->destination.x = x;
    object->destination.y = y;
    ((struct FrameActorObject *)object)->speed = speed;
    frame_set_actor_direction(object,
        frame_unrooted_refresh_destination_velocity_2b358(object));
    transition_object_set_state(object, 13);
}
