#include "frame_actor_runtime.h"
#include "view_math.h"
#include "frame_actor_direct_move.h"

/* Called by the independently bounded 8CD4 setup; other incoming roots unknown. */
unsigned char frame_unrooted_refresh_destination_velocity_2b358(
    struct FrameObject *object)
{
    int duration, delta_x, delta_y;
    unsigned char direction;

    duration = (int)(view_point_distance(object->destination,
                                         object->next_position.word) /
                     (unsigned int)((struct FrameActorObject *)object)->speed);
    if (duration < 0)
        duration = -duration;
    delta_x = (int)((unsigned int)object->destination.x -
                    (unsigned int)object->next_position.word.x);
    delta_y = (int)((unsigned int)object->destination.y -
                    (unsigned int)object->next_position.word.y);
    direction = frame_direction_from_velocity(object->velocity);
    object->velocity.x = delta_x / duration;
    object->velocity.y = delta_y / duration;
    return direction;
}
asm(".align 2, 0");
