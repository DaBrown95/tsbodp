#include "frame_controlled_actor.h"

void frame_enable_animation_part(struct FrameObject *base, unsigned char part)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    object->parts[part].flags |= 2;
}
