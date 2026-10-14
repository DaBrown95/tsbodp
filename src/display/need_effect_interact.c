#include "display_need_effect_update.h"

void frame_need_effect_interact(struct CollisionObject *first_base,
        struct CollisionObject *second_base)
{
    struct FrameObject *first = (struct FrameObject *)first_base;
    struct FrameObject *second = (struct FrameObject *)second_base;

    frame_need_effect_stop_at_position(first);
    frame_need_effect_stop_at_position(second);
}
