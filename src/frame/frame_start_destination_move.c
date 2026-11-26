#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_direct_move.h"

/* Independently bounded entry; incoming roots and unused formals are unknown. */
void frame_start_destination_move(struct FrameObject *object, int x, int y, int speed)
{
    object->destination.x = x;
    object->destination.y = y;
    ((struct FrameActorObject *)object)->speed = speed;
    frame_set_actor_direction(object, frame_refresh_destination_velocity(object));
    transition_object_set_state(object, 13);
}
