#include "resource_actor_entries.h"

int actor_entry_adjust_counter(void *input, int index, int change)
{
    unsigned char *record = input;
    int value;
    {
        unsigned char *cell = record + 4;
        value = cell[index] + change;
    }
    if (value > 250)
        value = 250;
    else if (value < 0)
        value = 0;
    {
        unsigned char *cell = record + 4;
        cell[index] = value;
    }
    condition_refresh_thresholds(record);
    return value;
}
asm(".align 2, 0");
