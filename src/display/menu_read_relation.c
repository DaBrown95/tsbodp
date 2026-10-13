#include "display_menu_relation.h"

signed char display_menu_read_relation(void *pointer, unsigned int index)
{
    struct DisplayMenuRelationValues *state = pointer;
    return state->records[index].value;
}

asm(".align 2, 0");
