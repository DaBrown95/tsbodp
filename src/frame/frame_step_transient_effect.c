#include "frame_render_effect.h"
#include "frame_transient_effect.h"
void frame_step_transient_effect(struct FrameTransientEffect *effect)
{
    unsigned int flags;
    unsigned int i;
    if(effect->owner && (effect->owner->flags&2))goto remove;
    {
        unsigned int loaded_flags=effect->flags;
        unsigned int lifetime=loaded_flags&2;
        flags=loaded_flags;
        if(lifetime && --effect->countdown==65535) {
            remove:
            frame_pool_release(g_frame_transient_free_pool,&g_frame_transient_active_list,(struct FrameObject *)effect);
            --g_frame_transient_count;
            return;
        }
    }
    if(!(flags&0x8000) && effect->unknown36++>=effect->width) {
        effect->unknown36=0;
        for(i=0;i<effect->enabled;i++) {
            if(g_frame_render_effect_count<=62 && !g_frame_render_effect_pending && !(effect->flags&0x40) &&
            ((effect->owner->flags&0x40000000) || (effect->flags&0x200)))
            frame_emit_transient_render_effect(effect);
        }
    }
}
asm(".align 2, 0");
