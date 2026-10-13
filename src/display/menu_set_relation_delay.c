#include "display_menu_relation_events.h"

void display_menu_set_relation_delay(void *pointer, unsigned int index,
                                     unsigned int delay)
{
    struct DisplayMenuRelationValues *state = pointer;
    state->records[index].flags &= ~8;
    state->records[index].unknown_02[0] = delay * 4;
}

asm(".align 2, 0");
