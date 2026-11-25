#include "display_menu_relation_events.h"

#include "frame_random.h"

void display_menu_try_relation_flag(void *pointer, unsigned int index)
{
    struct DisplayMenuRelationValues *state = pointer;
    signed char half;
    int probability;
    unsigned char chance;
#if TSBO_REVISION == 1
    /* Revision 1 never flags records 4, 7, 10 or 12. */
    if (index == 12 || index == 4 || index == 10 || index == 7)
        return;
#endif
    half = state->records[index].value / 2;
    probability = half;
    chance = 5;
    if (probability > 5)
        chance = half;
    if (frame_random_chance(chance))
        state->records[index].flags |= 8;
}

asm(".align 2, 0");
