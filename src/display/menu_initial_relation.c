#include "display_menu_relation.h"

int display_menu_initial_relation(struct DisplayMenuRelationState *state,
                                  unsigned int index)
{
    const struct DisplayMenuRelationTraits *own = (const void *)((unsigned char *)state + 0x18);
    const struct DisplayMenuRelationTraits *other = &g_display_menu_relation_traits[index];
    int value = g_display_menu_relation_seeds[index].initial;
    if (index != 12) {
        unsigned int i = 0;
        do {
            if (i == 4)
                value += (own->values[i] + other->values[i]) / 2;
            else {
                int first = own->values[i];
                int second = other->values[i];
                int difference = first - second;
                if (difference >= 0)
                    value -= difference / 2;
                else
                    value -= (second - first) / 2;
            }
            ++i;
        } while (i <= 4);
    }
    return value;
}

asm(".align 2, 0");
