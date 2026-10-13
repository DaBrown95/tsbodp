#include "resource_timed_actor.h"

void resource_timed_actor_choose_destination(struct FrameObject *base, unsigned int quadrant)
{
    struct ResourceTimedActor *object = (struct ResourceTimedActor *)base;
    int x = frame_random_range(1, 25);
    int y = frame_random_range(1, 25);

    if (quadrant <= 1) {
        object->destination.x = object->position.x + ((unsigned int)x << 16);
        object->destination.y = object->position.y + ((unsigned int)y << 16);
    } else if (quadrant <= 3) {
        object->destination.x = object->position.x + ((unsigned int)x << 16);
        object->destination.y = object->position.y - ((unsigned int)y << 16);
    } else if (quadrant <= 5) {
        object->destination.x = object->position.x - ((unsigned int)x << 16);
        object->destination.y = object->position.y - ((unsigned int)y << 16);
    } else {
        object->destination.x = object->position.x - ((unsigned int)x << 16);
        object->destination.y = object->position.y + ((unsigned int)y << 16);
    }
}
asm(".align 2,0");
