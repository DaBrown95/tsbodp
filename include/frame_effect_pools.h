#ifndef FRAME_EFFECT_POOLS_H
#define FRAME_EFFECT_POOLS_H
#include "frame_render_effect.h"
#include "frame_transient_effect.h"
#include "heap.h"

/* Typed storage views of the allocation pointers and intrusive free heads.
 * The existing unsigned-char free_pool symbols name their addresses for the
 * generic pool consumers; each free_head alias names the word at that root. */
extern struct FrameRenderEffect *g_frame_render_effect_backing;
extern struct FrameTransientEffect *g_frame_transient_backing;
extern struct FrameRenderEffect *g_frame_render_effect_free_head;
extern struct FrameTransientEffect *g_frame_transient_free_head;
void frame_initialize_effect_pools(void);
#endif
