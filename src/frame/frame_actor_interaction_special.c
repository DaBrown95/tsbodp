#include "frame_actor_runtime.h"
#include "input.h"
#include "scene_request_queue.h"

void frame_actor_interaction_special(struct FrameObject *base, struct FrameObject *other)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    struct FrameActorObject *actor = (struct FrameActorObject *)other;
    if (actor->id == 0 && (g_input_pressed[actor->unknown_13] & 1) &&
        object->subtype > 5 && object->subtype <= 17 && actor->state == 16) {
        resource_submit_scene(21, 0, object->subtype - 6);
        input_clear();
    }
}
