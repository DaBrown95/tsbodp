#include "display_need_effect_lifecycle.h"

void frame_need_effect_before_step(struct FrameObject *base)
{
    volatile struct FrameNeedEffectObject *object = (volatile struct FrameNeedEffectObject *)base;
    base->spatial.bounds.lower.x = ((struct DisplayNeedEffectStateView *)object->effect_state)->value_d4;
    base->spatial.bounds.lower.y = ((struct DisplayNeedEffectStateView *)object->effect_state)->value_d8;
    base->spatial.bounds.upper.x = ((struct DisplayNeedEffectStateView *)object->effect_state)->value_cc;
    base->spatial.bounds.upper.y = ((struct DisplayNeedEffectStateView *)object->effect_state)->value_d0;
}
asm(".align 2, 0");
