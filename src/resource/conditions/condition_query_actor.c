#include "resource_condition_entries.h"

int condition_query_actor(struct ConditionActorEntries *list, int kind)
{
    unsigned int index = 0;
    for (; index < list->count; index++) {
        if (list->entries[index].kind == kind)
            return (signed char)index;
    }
    return -1;
}
asm(".align 2, 0");
