#include "frame_daily_flag_creation.h"

void frame_daily_flag_interact(struct FrameObject *base, struct FrameObject *owner)
{
    struct FrameDailyFlagObject *object = (struct FrameDailyFlagObject *)base;
    if (owner->id == 0 && ((struct FrameActorObject *)owner)->state == 16 &&
        (g_input_pressed[0] & 1)) {
        transition_object_set_state((struct FrameObject *)object, 18);
        frame_set_variant_state((struct FrameObject *)object, 0);
        object->owner = owner;
        input_clear();
    }
}

asm(".align 2, 0");
