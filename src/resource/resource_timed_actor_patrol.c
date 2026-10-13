#include "resource_timed_actor.h"

void resource_timed_actor_patrol(struct FrameObject *base)
{
    struct ResourceTimedActor *object = (struct ResourceTimedActor *)base;
    switch (object->variant_state) {
    case 7:
        if (--object->countdown == -1) {
            if ((int)(view_point_distance(object->position, g_need_effect_player->position) >> 16) <= 49) {
                frame_set_variant_state(base, 9);
                object->countdown = 60;
            } else
                object->countdown = 20;
        }
        break;
    case 9: {
        unsigned int quadrant;
        unsigned char direction = frame_direction_to_destination(object->position, object->destination, object->speed);
        if (direction != object->direction) {
            if (direction == 8) {
                frame_set_variant_state(base, 7);
                object->countdown = 0;
                quadrant=frame_direction_away(base, g_need_effect_player);
            } else {
                object->direction = direction;
                object->pending_updates |= 16;
                break;
            }
        } else if (--object->countdown == -1) {
            object->countdown = 60;
            quadrant=frame_random_range(0, 7);
        } else {
            break;
        }
        resource_timed_actor_choose_destination(base, quadrant);
        break;
    }
    case 2:
        frame_set_variant_state(base, 7);
        object->countdown = 20;
        resource_timed_actor_choose_destination(base, frame_random_range(0, 7));
        break;
    }
}
asm(".align 2, 0");
