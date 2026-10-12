#include "frame_constructor.h"

void frame_enable_parts(struct FrameObject *base)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    int i;

    object->sharing_flags |= 0x40;
    for (i = 0; i < 4; i++) {
        object->parts[i].index |= 0xffff;
        object->parts[i].palette = object->oam.palette;
        object->parts[i].variants = 0;
    }
}
