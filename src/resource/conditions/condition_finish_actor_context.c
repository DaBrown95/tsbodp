#include "resource_conditions.h"
#include "condition_actor.h"

static inline int counter_value(struct ConditionCounter *input)
{
    register struct ConditionCounter *record asm("r0") = input;
    return record->value;
}

void condition_finish_actor_context(void *context)
{
    struct ConditionActorCounters *state = context;
    int value;
    value = counter_value(&state->counters[0]);
    if (value > 0) condition_complete_if_active(2, 2, 3);
    if (value > 4) condition_complete_if_active(3, 3, 1);
    value = counter_value(&state->counters[1]);
    if (value > 0) condition_complete_if_active(0, 3, 0);
    if (value > 1) condition_complete_if_active(2, 0, 1);
    value = counter_value(&state->counters[2]);
    if (value > 3) condition_complete_if_active(2, 1, 1);
    {
        struct ConditionCounter *counter = &state->counters[5];
        if (value > 2 && counter->value > 1)
            condition_complete_if_active(3, 2, 2);
    }
    value = counter_value(&state->counters[3]);
    if (value > 1) condition_complete_if_active(2, 1, 0);
    value = counter_value(&state->counters[4]);
    if (value > 3) condition_complete_if_active(3, 0, 2);
    if (value > 6) condition_complete_if_active(4, 3, 2);
}
