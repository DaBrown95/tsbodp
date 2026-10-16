#include "frame_actor_runtime.h"
#include "input.h"

void frame_actor_interaction_world31(struct FrameObject *base, struct FrameObject *other)
{
    struct FrameActorObject *actor = (struct FrameActorObject *)other;
    if (actor->id == 0 && (g_input_pressed[actor->unknown_13] & 1)) {
        frame_set_variant_state(base, 4);
        input_clear();
    }
}
