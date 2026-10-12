#include "condition_actor.h"

void condition_record_actor_selection(struct ConditionActorSelectionContext *state,
                                     unsigned char row, unsigned char column,
                                     unsigned char entry)
{
    unsigned int group, index;
    for (group = 0; group <= 12; group++) {
        struct ConditionActorGroup *current = &state->groups[group];
        struct ConditionActorDefinition *definitions = &g_condition_actor_definitions[group];
        for (index = 0; index < definitions->count; index++) {
            unsigned char *destination = current->values + index * 4;
            struct ConditionActorValue *definition = &definitions->values[index];
            if (definition->row == row && definition->column == column &&
                definition->entry == entry)
                *destination = definition->value;
        }
    }
}
asm(".align 2, 0");
