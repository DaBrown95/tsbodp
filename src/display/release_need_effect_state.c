#include "display_need_effect_lifecycle.h"

static inline struct FrameObject *load_actor(struct FrameActorAttachmentRecord *base,
                                           unsigned char i)
{
    unsigned int address = (unsigned int)base;
    address += i * 24;
    return *(struct FrameObject **)address;
}
unsigned int frame_release_need_effect_state(struct FrameNeedEffectState *base)
{
    struct DisplayNeedEffectStateView *state=(struct DisplayNeedEffectStateView *)base;
    unsigned char i;
    struct FrameActorAttachmentRecord *records;
    if(state->auxiliary_object) {
        transition_object_set_state(state->auxiliary_object,1);
        state->auxiliary_object=0;
    }
    i=0;
    records=base->records;
    for(;i<3;i++) {
        if(load_actor(records,i))
            frame_detach_actor(load_actor(records,i),(struct FrameObject *)state);
    }
    if(g_frame_need_effect_active_list.last==(struct FrameObject *)state)
        g_frame_need_effect_active_list.last=(struct FrameObject *)state->previous;
    frame_pool_release(&g_frame_need_effect_free_pool,&g_frame_need_effect_active_list,(struct FrameObject *)state);
    return 1;
}
