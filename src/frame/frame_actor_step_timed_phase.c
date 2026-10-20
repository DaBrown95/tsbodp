#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

void frame_actor_step_timed_phase(struct FrameObject *object, FrameU16 duration)
{
    switch (((struct FrameActorObject *)object)->variant_state) {
    case 2:
        if (--((struct FrameActorStateWork *)object)->timer == -1)
            frame_set_variant_state(object, 7);
        break;
    case 5:
        transition_object_set_state(object, 1);
        break;
    case 7:
        if (object->flags & 0x400000) {
            object->flags &= ~0x400000u;
            frame_set_variant_state(object, 2);
            ((struct FrameActorStateWork *)object)->timer = duration;
        }
        break;
    }
}
