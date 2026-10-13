#include "frame_render_effect.h"
struct FrameRenderEffect *frame_allocate_render_effect(void) {
 struct FrameRenderEffect *effect=(struct FrameRenderEffect *)frame_pool_allocate_08024d50(g_frame_render_effect_free_pool,(struct FrameObjectList *)&g_frame_render_effect_head,sizeof(*effect));
 if(++g_frame_render_effect_count>g_frame_render_effect_maximum)g_frame_render_effect_maximum=g_frame_render_effect_count;
 return effect;
}
