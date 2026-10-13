#include "display_menu_relation.h"

void display_menu_refresh_relation(void *pointer)
{
    struct DisplayMenuRelationMetrics *state = pointer;
    int total = 0;
    unsigned int index = 0;
    do {
        int value = state->records[index].value;
        if (value != -128)
            total += value;
        ++index;
    } while (index <= 23);
    state->average = total / 24;
}

asm(".align 2, 0");
