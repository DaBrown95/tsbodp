#include "frame_render_effect.h"
void frame_collect_objects(void)
{
    int layer;
    for (layer=0;layer<=3;layer++) {
        unsigned int count=0;
        struct FrameRenderEffect *effect=g_frame_render_effect_head;
        while(effect) {
            struct FrameRenderEffect *next=effect->next;
            unsigned int flags=effect->flags;
            if (!(flags&0x8000)) {
                if (effect->sprite.priority.layer==layer ||
                    ((flags&0x4000) && effect->sprite.priority.layer-1==layer)) {
                    unsigned int address=(unsigned int)g_frame_render_effect_lists[layer]; address+=count*4; *(struct FrameRenderEffect **)address=effect; count++;
                    effect->flags=flags|0x8000;
                }
            }
            effect=next;
        }
        g_frame_render_effect_counts[layer]=count;
    }
}
