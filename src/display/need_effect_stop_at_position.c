#include "display_need_effect_update.h"

void frame_need_effect_stop_at_position(struct FrameObject *base)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    unsigned short *flags;

    object->next_position.x = object->position.x;
    object->next_position.y = object->position.y;
    object->velocity.x = 0;
    object->velocity.y = 0;
    flags = (unsigned short *)((unsigned char *)base + 0xac);
    {
        unsigned int existing = *flags;
        unsigned int changed = 1;
        changed |= existing;
        *flags = changed;
    }
}
asm(".align 2, 0");
