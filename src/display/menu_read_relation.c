#include "display_menu_relation.h"

int display_menu_read_relation(void *pointer, unsigned int index)
{
    struct DisplayMenuRelationValues *state = pointer;
    return state->records[index].value;
}

asm(".align 2, 0");
