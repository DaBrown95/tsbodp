#include "frame_scene_player_update.h"

void frame_scene_initialize_player_state(struct FrameObject *base,
    unsigned char player)
{
    struct FrameActorObject *actor = (struct FrameActorObject *)base;

    actor->on_step = frame_scene_player_step_1dfe4;
    actor->unknown_13 = player;
    g_transition_view_context.views[
        g_transition_view_context.current_view].flags &= ~1;
    actor->flags |= 0x204;
    if (g_frame_scene_actor_selection.unknown0b[0x42e - 0x0b] == 0) {
        frame_request_animation((struct FrameCommandObject *)actor, 1);
        transition_object_set_state(actor, 16);
        frame_set_variant_state(base, 2);
    } else {
        frame_request_animation((struct FrameCommandObject *)actor, 86);
        transition_object_set_state(actor, 27);
        frame_set_variant_state(base, 0);
    }
}

asm(".align 2, 0");
