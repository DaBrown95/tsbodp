#include "display_menu_relation_events.h"

void display_menu_age_relation_delays(void *pointer)
{
    struct DisplayMenuRelationValues *state = pointer;
    unsigned int index = 0;
    unsigned char *delay = state->records[0].unknown_02;
    do {
        if (*delay != 0)
            --*delay;
        delay += 4;
        ++index;
    } while (index <= 23);
}

asm(".align 2, 0");
