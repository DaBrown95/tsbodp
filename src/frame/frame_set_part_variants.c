#include "frame_actor_group.h"

void frame_set_part_variants(struct FrameObject *base, unsigned char part,
                             struct FrameSpriteVariant **variants,
                             unsigned int palette)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    object->parts[part].variants = variants;
    object->parts[part].palette = palette;
}
