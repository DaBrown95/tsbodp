#include "display_need_effect_lifecycle.h"

void frame_reset_need_effect(struct FrameObject *base)
{
    struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
    object->phase=0;
    transition_object_set_state(base,0);
    heap_clear(object->effect_values,0,14);
    heap_clear(object->effect_choices,0,7);
    object->effect_flags=0;
}
asm(".align 2, 0");
