#include "frame_need_effect_clear.h"
#include "display_need_effect_lifecycle.h"

static inline struct FrameObject *attachment_actor(
    struct FrameActorAttachmentRecord *records, unsigned char index)
{
    unsigned int address = (unsigned int)records;
    address += index * sizeof(*records);
    return *(struct FrameObject **)address;
}
void frame_clear_need_effect_states(void)
{
    struct DisplayNeedEffectStateView *state =
        (void *)g_frame_need_effect_active_list.first;
    while (state) {
        struct FrameNeedEffectState *next = state->next;
        unsigned char i;
        struct FrameActorAttachmentRecord *records;
        if (state->auxiliary_object) {
            transition_object_set_state(state->auxiliary_object, 1);
            state->auxiliary_object = 0;
        }
        i = 0;
        records = ((struct FrameNeedEffectState *)state)->records;
        do {
            struct FrameObject *actor = attachment_actor(records, i);
            if (actor)
                frame_detach_actor(actor, (struct FrameObject *)state);
            i++;
        } while (i <= 2);
        if (g_frame_need_effect_active_list.last == (struct FrameObject *)state)
            g_frame_need_effect_active_list.last =
                (struct FrameObject *)state->previous;
        frame_pool_release(&g_frame_need_effect_free_pool,
            &g_frame_need_effect_active_list, (struct FrameObject *)state);
        state = (struct DisplayNeedEffectStateView *)next;
    }
}
