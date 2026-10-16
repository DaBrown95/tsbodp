#include "display_need_effect_update.h"
#include "input.h"
#include "scene_request_queue.h"

void frame_actor_interaction_default(struct FrameObject *base, struct FrameObject *other)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    struct FrameActorObject *actor = (struct FrameActorObject *)other;
    if (g_need_effect_game_state[0x42e] != 1 && actor->id == 0 &&
        (g_input_pressed[actor->unknown_13] & 1) && object->subtype > 17 &&
        actor->state == 16) {
        resource_submit_scene(15, 0, object->subtype - 18);
        audio_play_animation_cue(79);
        actor->indicator = base;
        input_clear();
    }
}
