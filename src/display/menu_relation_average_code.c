#include "display_menu_relation_average.h"

int display_menu_relation_average_code(struct DisplayMenuRelationState *state)
{
    int average = state->values.average;
    int index = 14;
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
    return index + 473;
}

asm(".align 2, 0");
