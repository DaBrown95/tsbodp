#include "display_need_effect_lifecycle.h"

unsigned char frame_need_effect_enabled(struct FrameObject *base)
{
    struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
    if(g_frame_world_id==9&&object->subtype==141)return 0;
    if(frame_world_in_idle_exclusion_set(g_frame_world_id)||
            ((struct DisplayNeedEffectStateView *)object->effect_state)->unknown_63==1||object->effect_state->enabled==1)return 1;
    return 0;
}
