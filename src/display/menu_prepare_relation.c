#include "display_menu_relation.h"

void display_menu_prepare_relation(void *pointer, unsigned int index)
{
    struct DisplayMenuRelationState *state = pointer;
    if (state->values.records[index].value == -128)
        display_menu_write_relation(state, index,
                                    display_menu_initial_relation(state, index));
}

asm(".align 2, 0");
