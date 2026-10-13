#include "frame_render_effect.h"
void frame_destroy_render_effect(struct FrameRenderEffect *effect){
 frame_pool_release(g_frame_render_effect_free_pool,(struct FrameObjectList *)&g_frame_render_effect_head,(struct FrameObject *)effect);
 g_frame_render_effect_count--;
}
