#include "display_need_effect_lifecycle.h"

struct FrameNeedEffectState *frame_create_need_effect_state_node(void)
{
    struct FrameNeedEffectState *state=(struct FrameNeedEffectState *)frame_pool_allocate_08024d50(&g_frame_need_effect_free_pool,&g_frame_need_effect_active_list,256);
    if(state&&!g_frame_need_effect_active_list.last)g_frame_need_effect_active_list.last=(struct FrameObject *)state;
    return state;
}
asm(".align 2, 0");
