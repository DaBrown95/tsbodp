#include "frame_actor_runtime.h"
#include "frame_transient_effect.h"
void frame_destroy_transient_effect(struct FrameTransientEffect *effect)
{
 frame_pool_release(g_frame_transient_free_pool,&g_frame_transient_active_list,(struct FrameObject *)effect);
 g_frame_transient_count--;
}
