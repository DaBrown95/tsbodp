#include "display_menu_relation.h"

unsigned char display_menu_relation_flags(void *pointer, unsigned int index)
{
    struct DisplayMenuRelationValues *state = pointer;
    return state->records[index].flags;
}

asm(".align 2, 0");
