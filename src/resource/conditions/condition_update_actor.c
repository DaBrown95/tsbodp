#include "resource_condition_entries.h"

void condition_update_actor(struct ConditionActorEntries *list, int index,
                            unsigned char compact)
{
    if (compact) {
        int count = list->capacity - index;
        int remaining = count - 2, previous;
        if (count != 1) {
            do {
                list->entries[index] = list->entries[index + 1];
                index++;
                previous = remaining;
                remaining--;
            } while (previous);
        }
    }
    list->entries[index].kind = 0xff;
    list->entries[index].value1 = 0;
    list->entries[index].value2 = 0;
    list->count--;
}
asm(".align 2, 0");
