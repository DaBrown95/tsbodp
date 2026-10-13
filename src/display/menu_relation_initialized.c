#include "display_menu_relation_events.h"

unsigned char display_menu_relation_initialized(void *pointer, unsigned int index)
{
    struct DisplayMenuRelationValues *state = pointer;
    return state->records[index].value != -128;
}

asm(".align 2, 0");
