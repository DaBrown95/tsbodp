#include "frame_actor_items.h"

void frame_emit_actor_item_contact(struct FrameObject *object, unsigned char positive)
{
    struct FrameTransientEffect *effect;

    if (positive)
        effect = frame_create_transient_effect(15, 0, 1);
    else
        effect = frame_create_transient_effect(15, 0, 0);
    if (effect) {
        effect->owner = object;
        effect->phase = 3;
        effect->height = 30;
        effect->enabled = 1;
        effect->countdown = 8;
        effect->unknown34 = 0;
        effect->direction = g_frame_transient_extended_directions[
            ((struct FrameActorObject *)object)->direction];
        effect->rate = 65536;
        effect->mode = 2;
        effect->flags |= 0x35082;
    }
}
asm(".align 2,0");
