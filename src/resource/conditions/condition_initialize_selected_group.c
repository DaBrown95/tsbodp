#include "resource_commands.h"
#include "resource_conditions.h"
#include "resource_condition_selection.h"

/* Byte-root alias eight bytes into the 32-byte definition rows. */
extern unsigned char g_condition_definition_columns[];

static inline unsigned int selected_entry_kind(struct ConditionDefinition *definition,
                                               unsigned int entry)
{
    register unsigned char *kinds asm("r0");
    register unsigned char *element asm("r1");
    kinds = (unsigned char *)definition + 4;
    element = kinds + entry;
    return *element;
}

static inline unsigned char *selected_entry_start(unsigned int row_offset,
                                                  unsigned int column_offset)
{
    unsigned int row_start = (unsigned int)&g_resource_game_state;
    unsigned int selected_start;
    row_start += 0x448;
    row_start = row_offset + row_start;
    selected_start = column_offset;
    selected_start += row_start;
    return (unsigned char *)selected_start;
}

static inline unsigned int state_address(unsigned int row_offset,
                                         unsigned int column_offset)
{
    unsigned int base = (unsigned int)&g_resource_game_state;
    return column_offset + row_offset + base;
}

void condition_initialize_selected_group(unsigned int row_in, unsigned int column_in)
{
    unsigned int row = row_in, column = column_in;
    if (row <= 1) {
        unsigned int index = 0;
        unsigned int definition_offset = row * 32;
        unsigned int row_units = row * 8;
        if (index < column) {
            register unsigned int row_offset asm("r8") = (row_units + row) * 16;
            register unsigned int enabled asm("r4") = 1;
            register unsigned int entry_row_offset asm("r9") = row_offset;
            do {
                register struct ConditionDefinition *definition asm("r6") =
                    *(struct ConditionDefinition **)((unsigned int)g_condition_definition_columns +
                                                     definition_offset + index * 4);
                register unsigned int entry asm("r5");
                unsigned int column_offset = index * 24;
                unsigned int next;
                unsigned int address = state_address(row_offset, column_offset);
                *(unsigned char *)(address + 0x444) = enabled;
                *(unsigned char *)(address + 0x445) = enabled;
                entry = 0;
                next = index + 1;
                if (entry < definition->count) {
                    unsigned char *cursor =
                        (unsigned char *)(state_address(entry_row_offset, column_offset) + 0x448);
                    do {
                        cursor[0] = enabled;
                        cursor[1] = enabled;
                        cursor += 4;
                        ++entry;
                    } while (entry < definition->count);
                }
                index = next;
            } while (index < column);
        }
    }
    {
        register struct ConditionDefinition *definition asm("r6") =
            g_condition_definitions[row].columns[column];
        register unsigned int entry asm("r5");
        unsigned int column_offset = column * 24, row_offset = row * 144;
        {
            unsigned int address = state_address(row_offset, column_offset);
            *(unsigned char *)(address + 0x444) = 1;
            *(unsigned char *)(address + 0x445) = 1;
        }
        entry = 0;
        if (entry < definition->count) {
            unsigned int marked;
            unsigned char *state;
            marked = 1;
            state = selected_entry_start(row_offset, column_offset);
            do {
                state[0] = marked;
                state[1] = marked;
                {
                    unsigned char kind = selected_entry_kind(definition, entry);
                    if (kind != 0xff)
                        resource_set_display_kind(kind);
                }
                state += 4;
                entry++;
            } while (entry < definition->count);
        }
        if (definition->display_kind != 0xff)
            resource_set_display_kind(definition->display_kind);
    }
}
asm(".align 2, 0");
