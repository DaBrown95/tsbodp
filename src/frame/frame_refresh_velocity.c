#include "frame_constructor.h"

void frame_refresh_velocity(struct FrameObject *base)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    struct FramePoint velocity;

    frame_make_velocity(&velocity, object->flags, object->direction, object->speed);
    object->velocity.x = velocity.x;
    object->velocity.y = velocity.y;
}

asm(".align 2, 0");
