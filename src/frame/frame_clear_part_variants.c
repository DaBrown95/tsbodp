#include "frame_actor_group.h"

void frame_clear_part_variants(struct FrameObject *base, unsigned char part)
{
    ((struct FrameActorObject *)base)->parts[part].variants = 0;
}
