#include "display_menu_relation.h"
#include "resource_conditions.h"

int display_menu_write_relation(struct DisplayMenuRelationState *state,
                                unsigned int index, int value)
{
    state->values.records[index].value = value;
    display_menu_refresh_relation(&state->values);
    condition_update_actor_context(state);
    return value;
}

asm(".align 2, 0");
