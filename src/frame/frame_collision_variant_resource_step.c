#include "frame_collision_variant_resource.h"
#include "display_need_effect_update.h"

void frame_collision_variant_resource_step(struct FrameObject *object)
{
    struct FrameCollisionVariantView *view = (void *)object;

    switch (view->state) {
    case 0: break;
    case 1:
        if (!(object->flags & 0x1000))
            object->flags = (object->flags & ~1) | 2;
        break;
    }
    view->pending_updates = 0;
}

/* Original zero-filled alignment, separate from the C instruction body. */
asm(".align 2, 0");
