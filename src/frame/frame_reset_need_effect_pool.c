#include "frame_actor_initialization.h"
#include "display_need_effect_lifecycle.h"

void frame_reset_need_effect_pool(void)
{
    g_frame_need_effect_free_pool = (struct FrameNeedEffectState *)
        frame_pool_initialize(g_frame_need_effect_storage, 128, 256);
    g_frame_need_effect_active_list.first = 0;
    g_frame_need_effect_active_list.last = 0;
}
