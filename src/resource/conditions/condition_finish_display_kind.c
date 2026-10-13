#include "save_condition_state.h"

void condition_finish_display_kind(unsigned int kind)
{
    unsigned char index = 0;

    while (g_condition_display_completions[index].kind != 119) {
        const struct ConditionDisplayCompletion *completion =
            &g_condition_display_completions[index];
        if (kind == completion->kind)
            condition_finish_group(completion->row, completion->column);
        ++index;
    }
    g_condition_display_bits[kind >> 3] &= ~(1 << (kind & 7));
}

asm(".align 2, 0");
