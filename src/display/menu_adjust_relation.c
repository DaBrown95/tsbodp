#include "display_menu_relation.h"

int display_menu_adjust_relation(struct DisplayMenuRelationState *state,
                                 unsigned int index, int delta)
{
    int previous = state->values.records[index].value;
    int value;
    if (previous == -128)
        return previous;
    value = previous + delta;
    if (value < -100)
        value = -100;
    else if (value > 100)
        value = 100;
    if (value <= 0)
        state->values.records[index].flags &= ~8;
    if (delta > 0) {
        if (value > 49 && previous <= 49) {
            state->values.records[index].flags |= 4;
            ++state->values.high_count;
        } else if (value > -50 && previous <= -50)
            state->values.records[index].flags &= ~2;
        else if (value > -90 && previous <= -90)
            state->values.records[index].flags &= ~1;
    } else {
        if (value <= 49 && previous > 49) {
            state->values.records[index].flags &= ~4;
            --state->values.high_count;
        } else if (value <= -50 && previous > -50)
            state->values.records[index].flags |= 2;
        else if (value <= -90 && previous > -90)
            state->values.records[index].flags |= 1;
    }
    display_menu_write_relation(state, index, value);
    return value;
}

asm(".align 2, 0");
