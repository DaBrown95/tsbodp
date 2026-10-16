#include "frame_effect_pools.h"

void frame_initialize_effect_pools(void)
{
    unsigned int layer;
    g_frame_render_effect_backing = heap_allocate_zeroed(64 * sizeof(struct FrameRenderEffect));
    g_frame_transient_backing = heap_allocate_zeroed(15 * sizeof(struct FrameTransientEffect));
    g_frame_render_effect_free_head = (struct FrameRenderEffect *)frame_pool_initialize(
        g_frame_render_effect_backing, 64, sizeof(struct FrameRenderEffect));
    g_frame_transient_free_head = (struct FrameTransientEffect *)frame_pool_initialize(
        g_frame_transient_backing, 15, sizeof(struct FrameTransientEffect));
    for (layer = 0; layer < 4; ++layer)
        g_frame_render_effect_lists[layer] = heap_allocate_zeroed(256);
    g_frame_render_effect_head = 0;
    g_frame_transient_active_list.first = 0;
    g_frame_render_effect_count = 0;
    g_frame_render_effect_maximum = 0;
    g_frame_transient_count = 0;
    g_frame_transient_maximum = 0;
    g_frame_render_effect_pending = 0;
}
