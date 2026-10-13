#include "save_world_initialization.h"

void save_world_initialize_conditions(void)
{
    struct SaveWorldConditionBlock *state = &g_save_world_condition_block;
    unsigned int index;
    heap_clear(state, 0, 724);
    condition_clear_display_bits();
    state->selected = 0;
    for (index = 0; index <= 22; ++index)
        resource_set_display_kind(index);
    condition_publish_row_displays(g_save_world_condition_source.row);
}
asm(".align 2, 0");
