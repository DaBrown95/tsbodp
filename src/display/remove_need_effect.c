#include "display_need_effect_lifecycle.h"

void frame_need_effect_remove(struct FrameObject *base)
{
    if(((struct FrameNeedEffectObject *)base)->effect_state) {
        if(((struct FrameNeedEffectObject *)base)->mode==1)
            frame_unregister_need_effect(g_frame_registration,base);
        if(((struct FrameNeedEffectObject *)base)->effect_state) {
            frame_release_need_effect_state(((struct FrameNeedEffectObject *)base)->effect_state);
            ((struct FrameNeedEffectObject *)base)->effect_state=0;
        }
    }
}
asm(".align 2, 0");
