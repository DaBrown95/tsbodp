#include "resource_timed_actor.h"

void resource_timed_actor_interact(struct FrameObject *base, struct FrameObject *target)
{
    struct ResourceTimedActor *object = (struct ResourceTimedActor *)base;
    unsigned int reach = (unsigned int)object->unknown_ae << 16;
    unsigned int distance = view_point_distance(object->next_position, target->next_position);

    if (target->id == 0 && distance <= reach + 20)
        frame_set_variant_state(base, 9);
}
asm(".align 2, 0");
