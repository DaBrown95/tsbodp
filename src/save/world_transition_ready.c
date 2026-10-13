#include "save_world_initialization.h"

unsigned int save_world_transition_ready(unsigned int index)
{
    struct SaveWorldTransitionRow *table = g_save_world_transition_rows;
    struct SaveWorldTransitionRow *row = &table[index];
    if (row->ready == 1) return 1;
    return 0;
}
asm(".align 2, 0");
