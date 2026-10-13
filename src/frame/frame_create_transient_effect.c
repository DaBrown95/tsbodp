#include "frame_actor_runtime.h"
#include "frame_transient_effect.h"
struct FrameTransientEffect *frame_create_transient_effect(unsigned char kind,unsigned char group,unsigned char index)
{
 struct FrameTransientEffect *effect;
 if(g_frame_transient_count<=13) {
 effect=(struct FrameTransientEffect *)frame_pool_allocate_08024d50(g_frame_transient_free_pool,&g_frame_transient_active_list,sizeof(*effect));
 if(++g_frame_transient_count>g_frame_transient_maximum)g_frame_transient_maximum=g_frame_transient_count;
 effect->kind=kind;
 effect->index=g_frame_transient_definitions[group][index].index;
 effect->resource=g_frame_transient_definitions[group][index].resource;
 effect->rate=0x20000;
 effect->frames=g_frame_transient_definitions[group][index].frames;
 effect->mode=0;
 return effect;
 }
 return 0;
}
