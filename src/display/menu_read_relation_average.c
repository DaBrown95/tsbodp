#include "frame_optional_choice_apply.h"

int display_menu_read_relation_average(struct DisplayMenuRelationState *state)
{
    return ((struct DisplayMenuRelationMetrics *)((unsigned int)state + 0x20))->average;
}
asm(".align 2, 0");
