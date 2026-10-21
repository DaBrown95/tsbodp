#include "save_world_initialization.h"

void save_world_initialize_relations(struct DisplayMenuRelationState *state)
{
    unsigned int index = 0;
    signed char initial = -128;
    struct DisplayMenuRelationRecord *record = state->values.records;
    const struct DisplayMenuRelationSeed *seed = g_display_menu_relation_seeds;
    do {
        record->flags = seed->unknown_00;
        record->value = initial;
        ++record;
        ++seed;
        ++index;
    } while (index <= 23);
    display_menu_refresh_relation(&state->values);
}
asm(".align 2, 0");
