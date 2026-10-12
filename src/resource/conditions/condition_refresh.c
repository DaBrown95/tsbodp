#include "resource_commands.h"
#include "resource_conditions.h"

unsigned int condition_refresh(unsigned int row_in, unsigned int column_in)
{
    unsigned int row = row_in, column = column_in;
    unsigned int all = 1, index = 0, limit;
    register unsigned int address asm("r1");

    {
        unsigned int count = g_condition_definitions[row].columns[column]->count;
        if (index >= count)
            goto finished;
        {
            register unsigned char *state asm("r2") =
                (unsigned char *)&g_resource_game_state;
            address = column * 24;
            address += row * 144;
            address += (unsigned int)state;
        }
        limit = count;
    }

    do {
        register unsigned int offset asm("r5") = 0x449;
        register unsigned char *active asm("r0");
        if (!*(unsigned char *)(address + offset)) {
            all = 0;
        } else {
            active = (unsigned char *)(address + --offset);
            if (!*active)
                all = 0;
        }
        address += 4;
        index++;
    } while (index < limit);

finished:
    if (all) {
        struct ConditionDefinition *definition =
            g_condition_definitions[row].columns[column];
        unsigned char kind = definition->display_kind;
        if (kind != 0xff)
            resource_set_display_kind(kind);
    }
    return all;
}
