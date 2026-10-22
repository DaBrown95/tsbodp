#include "display_menu_relation_average.h"

int display_menu_relation_average_band(struct DisplayMenuRelationState *state)
{
    int average = state->values.average;
    register int index asm("r1") = 14;
    const struct DisplayMenuRelationAverageBand *band =
        g_display_menu_relation_average_bands;

    if (average < band[14].threshold) {
        band += 14;
        do {
            --band;
            --index;
            if (index == 0)
                break;
        } while (average < band->threshold);
    }
    return index;
}

asm(".align 2, 0");
