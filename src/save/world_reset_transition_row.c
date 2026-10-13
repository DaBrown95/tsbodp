#include "save_world_initialization.h"

void save_world_reset_transition_row(unsigned int index)
{
    struct SaveWorldTransitionRow *table = g_save_world_transition_rows;
    struct SaveWorldTransitionRow *row = &table[index];
    row->ready = 1;
    row->ticks = 0;
}
asm(".align 2, 0");
