#include "display_menu_relation_events.h"

extern unsigned char frame_random_chance(unsigned char);

void display_menu_try_relation_flag(void *pointer, unsigned int index)
{
    struct DisplayMenuRelationValues *state = pointer;
    signed char half = state->records[index].value / 2;
    int probability = half;
    unsigned char chance = 5;
    if (probability > 5)
        chance = half;
    if (frame_random_chance(chance))
        state->records[index].flags |= 8;
}

asm(".align 2, 0");
