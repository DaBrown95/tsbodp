#include "resource_commands.h"
#include "resource_conditions.h"

static inline unsigned int group_address(unsigned int row, unsigned int column)
{
    unsigned int base = (unsigned int)&g_resource_game_state;
    unsigned int offset = column * 24;
    offset += row * 144;
    return offset + base;
}

static inline unsigned int entry_address(unsigned int row, unsigned int column,
                                         unsigned int entry)
{
    unsigned int base = (unsigned int)&g_resource_game_state;
    unsigned int offset = entry * 4;
    offset += column * 24;
    offset += row * 144;
    return offset + base;
}

void condition_initialize_prior_rows(unsigned int selected)
{
    unsigned char row, column, entry;
    for (row = 0; row < selected; row++) {
        for (column = 0; column < g_condition_definitions[row].count; column++) {
            struct ConditionDefinition *definition = g_condition_definitions[row].columns[column];
            {
                unsigned int address = group_address(row, column);
                *(unsigned char *)(address + 0x444) = 1;
                *(unsigned char *)(address + 0x445) = 1;
            }
            for (entry = 0; entry < definition->count; entry++) {
                unsigned int address = entry_address(row, column, entry);
                *(unsigned char *)(address + 0x448) = 1;
                *(unsigned char *)(address + 0x449) = 1;
            }
        }
    }
    condition_select_row(selected);
}
asm(".align 2, 0");
