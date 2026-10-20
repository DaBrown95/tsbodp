#include "display_need_effect_lifecycle.h"

static inline void **advance_output(void **out)
{
    return (void **)((unsigned int)out + sizeof(*out));
}
static inline void *definition_callback(const unsigned char *base, unsigned int offset,
                                        unsigned int field)
{
    register const unsigned char *address asm("r0") = base + field;
    return *(void **)(offset + (unsigned int)address);
}
struct FrameNeedEffectState *frame_allocate_need_effect_state(unsigned int original_kind)
{
    unsigned int kind=original_kind;
    struct DisplayNeedEffectStateView *state=(struct DisplayNeedEffectStateView *)frame_create_need_effect_state_node();
    if(state) {
        const unsigned char *definitions;
        unsigned int offset;
        struct DisplayNeedEffectDefinitionView *definition;
        void **out;
        register const unsigned char *last_base asm("r0");
        state->kind=kind;
        state->object=0;
        definitions=(const unsigned char *)g_frame_need_effect_definitions;
        offset=kind*36;
        definition=(struct DisplayNeedEffectDefinitionView *)(offset+(unsigned int)definitions);
        state->definition_20=definition->definition_20;
        state->definition_21=definition->definition_21;
        state->definition_22=definition->definition_22;
        state->unknown_63=0;
        state->optional=0;
        state->parameter=0;
        heap_clear(state->work_74,0,48);
        heap_clear(state->work_a4,0,40);
        state->value_d4=0;
        state->value_d8=0;
        state->value_cc=0;
        state->value_d0=0;
        state->value_dc=0;
        out=&state->callback_e4;
        *out=definition_callback(definitions,offset,28);
        out=advance_output(out);
        *out=definition_callback(definitions,offset,4);
        out=advance_output(out);
        *out=definition_callback(definitions,offset,8);
        out=advance_output(out);
        *out=definition_callback(definitions,offset,12);
        out=advance_output(out);
        *out=definition_callback(definitions,offset,16);
        out=advance_output(out);
        *out=definition_callback(definitions,offset,20);
        out=advance_output(out);
        last_base=definitions+24;
        offset+=(unsigned int)last_base;
        *out=*(void **)offset;
        heap_clear(((struct FrameNeedEffectState *)state)->records,0,72);
    }
    return (struct FrameNeedEffectState *)state;
}
asm(".align 2, 0");
