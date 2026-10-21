#include "frame_actor_runtime.h"
#include "frame_actor_distance.h"

/* Only incoming R1 is read. The unused R0 slot carries no object claim. */
void frame_obstacle_turn_unrooted_11520(void *unused, struct FrameObject *base)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    if (object->variant_state != 13) {
        object->direction = g_actor_obstacle_directions[object->direction * 2];
        frame_set_variant_state(base, 13);
        ((struct FrameActorFollowWork *)base)->timer = 20;
        object->pending_updates |= 0x12;
    }
}
