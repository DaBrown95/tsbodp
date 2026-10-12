#include "frame_constructor.h"

void frame_set_part_order(struct FrameObject *base, FrameU8 part, FrameU8 order)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    object->parts[part].order = order;
}

asm(".align 2, 0");
