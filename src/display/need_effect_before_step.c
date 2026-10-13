#include "display_need_effect_lifecycle.h"

static inline unsigned char *advance(unsigned char *out)
{
    register unsigned char *next = out + 4;
    return next;
}
void frame_need_effect_before_step(struct FrameObject *base)
{
    volatile struct FrameNeedEffectObject *object = (volatile struct FrameNeedEffectObject *)base;
    unsigned char *out = object->unknown_9c;
    *(unsigned int *)out = ((struct DisplayNeedEffectStateView *)object->effect_state)->value_d4;
    out = advance(out);
    *(unsigned int *)out = ((struct DisplayNeedEffectStateView *)object->effect_state)->value_d8;
    out = advance(out);
    *(unsigned int *)out = ((struct DisplayNeedEffectStateView *)object->effect_state)->value_cc;
    out = advance(out);
    *(unsigned int *)out = ((struct DisplayNeedEffectStateView *)object->effect_state)->value_d0;
}
asm(".align 2, 0");
