#ifndef DISPLAY_MENU_RELATION_AVERAGE_H
#define DISPLAY_MENU_RELATION_AVERAGE_H

#include "display_menu_relation.h"

/* Observed eight-byte ROM rows; these readers do not use the second word. */
struct DisplayMenuRelationAverageBand {
    int threshold;
    unsigned int unknown_04;
};
extern const struct DisplayMenuRelationAverageBand
    g_display_menu_relation_average_bands[];

/* Provisional consumed views of unrooted readers. Historical unused formals
 * and incoming roots remain unknown. Results are full words. */
int display_menu_relation_average_band(struct DisplayMenuRelationState *);
int display_menu_relation_average_code(struct DisplayMenuRelationState *);

#endif
