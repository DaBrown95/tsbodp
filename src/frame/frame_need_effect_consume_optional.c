#include "frame_need_effect_optional_jobs.h"

static inline unsigned char definition_amount(const unsigned char *table,
                                               unsigned int kind)
{
    unsigned int offset = kind * 36;
    return table[offset + 35];
}

static inline unsigned int mask_input(unsigned int value, unsigned int mask)
{
    unsigned int result = mask;
    result &= value;
    return result;
}

unsigned int frame_need_effect_consume_optional(struct FrameNeedEffectState *state,
                                                struct FrameActorAttachmentRecord *record,
                                                struct FrameObject *indicator)
{
    unsigned short cost = (unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe, 1) * 4 + 43;
    unsigned short *parameter;
    unsigned char optional;
    unsigned char *optional_pointer;

    if (mask_input(g_input_pressed[g_input_config.local_player], 1) == 1)
        cost = (((unsigned int)cost << 16) + 0x190000) >> 16;
    optional = state->optional;
    optional_pointer = &state->optional;
    parameter = &state->parameter;
    if (optional == 1) {
        unsigned int old = *parameter;
        int value = *(short *)parameter;
        int debit = (short)cost;
        if (value > debit) {
            *parameter = old - debit;
            frame_adjust_actor_needs((struct FrameActorNeedState *)((struct FrameActorObject *)record->actor)->actor_state,
                                    18, definition_amount((const unsigned char *)g_frame_need_effect_definitions, state->kind));
            frame_set_attachment_parameter_indicator(indicator, 100 - (*(short *)parameter >> 8));
            return 0;
        }
    }
    {
        unsigned int zero = 0;
        *optional_pointer = zero;
        *parameter = zero;
    }
    return 1;
}
asm(".align 2, 0");
