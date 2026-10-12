#include "frame_actor_runtime.h"
#include "frame_layer.h"

/* The retained state-update name is provisional; this applies the OAM layer. */
void frame_update_actor_state(struct FrameObject *base)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    struct FramePoint position = {
        ((short *)&object->next_position)[1],
        ((short *)&object->next_position)[3]
    };
    object->oam.layer = frame_layer_at_position(position);
}

asm(".align 2, 0");
