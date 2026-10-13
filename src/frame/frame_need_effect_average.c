#include "frame_need_effect_average.h"

unsigned char frame_need_effect_average(unsigned char *output_count)
{
    unsigned short total = 0;
    unsigned char count = 0;
    struct FrameNeedEffectState *state =
        (void *)g_frame_need_effect_active_list.first;

    if (state) {
        const struct FrameNeedEffectAverageCallbackEntry *definitions =
            g_frame_need_effect_average_callbacks;
        do {
            struct FrameNeedEffectState *next =
                ((struct DisplayNeedEffectStateView *)state)->next;
            if ((unsigned char)(state->optional - 1) <= 1) {
                int adjustment = ((short)state->parameter >> 8) - 100;
                int prior = (short)total;
                total = prior - adjustment;
            } else {
                unsigned char (*query)(struct FrameNeedEffectState *) =
                    definitions[state->kind].query;
                if (query)
                    total += query(state);
                else
                    total += 100;
            }
            count++;
            state = next;
        } while (state);
    }
    {
        unsigned char result;
        if (count)
            result = display_bios_div(total, count);
        else
            result = 50;
        if (output_count)
            *output_count = count;
        return result;
    }
}

asm(".align 2, 0");
