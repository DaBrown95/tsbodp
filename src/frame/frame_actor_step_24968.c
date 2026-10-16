#include "frame_actor_24420.h"

void frame_actor_step_24968(struct FrameObject *base)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;

    frame_actor_update_24720(base);
    if (object->pending_updates & 0x16) {
        if (object->pending_updates & 0x14)
            frame_set_animation_variant(base,
                ((struct FrameActorGroupAnimationView *)object)->animation,
                g_frame_scene_double_direction_variants[object->direction]);
        if (object->direction > 8)
            object->oam.flip_x = 1;
        else
            object->oam.flip_x = 0;
    }
    object->pending_updates = 0;
}
