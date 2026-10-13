#include "display_need_effect_choices.h"

/* The scan's title lookup uses a short offset/result register view. */
static inline unsigned int read_title(struct DisplayNeedEffectActionText *table,
                                     unsigned int code)
{
    register unsigned int offset asm("r0") = code << 2;
    return ((struct DisplayNeedEffectActionText *)
            (offset + (unsigned int)table))->text;
}

static inline unsigned short read_action_title(
    struct DisplayNeedEffectActionText *input, unsigned int code)
{
    register struct DisplayNeedEffectActionText *record asm("r0") = input;
    record += code;
    return record->text;
}

static inline unsigned short game_flag(void)
{
    register unsigned char *state asm("r0") = g_need_effect_game_state;
    return *(unsigned short *)(state + 0x744);
}

unsigned char frame_need_effect_build_choices(struct FrameObject *base)
{
    struct FrameNeedEffectState *state =
        ((struct FrameNeedEffectObject *)base)->effect_state;
    void (**callback)(struct FrameNeedEffectState *, unsigned char *) =
        &((struct DisplayNeedEffectChoiceCallback *)state)->actions;
    register unsigned char *choices asm("r5") =
        ((struct FrameNeedEffectObject *)base)->effect_choices;
    register unsigned short *values asm("r4");
    unsigned char count, j;
    unsigned int i;
    register unsigned char *secondary_choices asm("r10");

    (*callback)(state, choices);
    values = (unsigned short *)((struct FrameNeedEffectObject *)base)->effect_values;
    heap_clear(values, 0, 14);
    count = 0;
    i = 0;
    secondary_choices = choices;
    {
        register struct DisplayNeedEffectActionText *table asm("r3") =
            g_need_effect_action_text;
        {
            register unsigned int code asm("r2");
scan:
            code = choices[i];
            if (!code)
                goto scanned;
            {
                unsigned int destination;
                {
                    register unsigned int offset asm("r1") = i << 1;
                    destination = (unsigned int)values + offset;
                }
                *(unsigned short *)destination = read_title(table, code);
            }
            count++;
            i = (unsigned char)(i + 1);
            if (i <= 6)
                goto scan;
scanned:;
        }
    }
    if (frame_need_effect_enabled(base) == 1 && i <= 6 &&
        frame_need_effect_attachment_count(state) == 0 && state->optional != 3 &&
        state->kind != 133 && state->kind != 135 &&
        state->kind != 146 && state->kind != 147) {
        unsigned int offset, destination;
        {
            register unsigned int code asm("r2") = 40;
            register unsigned char *pointer asm("r0");
            pointer = choices + i;
            *pointer = code;
        }
        offset = i << 1;
        destination = (unsigned int)base + 0x6c;
        destination += offset;
        *(unsigned short *)destination = read_action_title(g_need_effect_action_text, 40);
        i = (unsigned char)(i + 1);
        count++;
    }
    if (frame_world_in_idle_exclusion_set(g_frame_world_id) == 1 && i <= 6 &&
        frame_need_effect_attachment_count(state) == 0 && state->optional != 3 &&
        state->kind != 133 && state->kind != 135 &&
        state->kind != 146 && state->kind != 147) {
        unsigned int offset, destination;
        {
            register unsigned int code asm("r2") = 34;
            register unsigned char *pointer asm("r0");
            pointer = secondary_choices + i;
            *pointer = code;
        }
        offset = i << 1;
        destination = (unsigned int)base + 0x6c;
        destination += offset;
        *(unsigned short *)destination = read_action_title(g_need_effect_action_text, 34);
        count++;
    }
    if (count) {
        g_need_effect_choice_counters.value_4 = 0;
        g_need_effect_choice_counters.value_1 = 0;
        g_need_effect_choice_counters.value_2 = 0;
        {
            unsigned short *source, *destination;
            j = 0;
            destination = g_need_effect_choice_text;
            source = (unsigned short *)((struct FrameNeedEffectObject *)base)->effect_values;
            do {
                destination[j] = *(unsigned short *)((unsigned int)source + (j << 1));
                j++;
            } while (j <= 6);
        }
        if (state->kind == 117)
            display_text_number_field_two(game_flag());
        display_scene_stage_08027dc0(2);
        transition_object_set_state(base, 15);
        frame_set_variant_state(base, 0);
        return 1;
    }
    return 0;
}
asm(".align 2, 0");
