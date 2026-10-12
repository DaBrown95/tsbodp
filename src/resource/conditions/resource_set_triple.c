#include "resource_commands.h"
#include "resource_conditions.h"

struct ConditionSelection {
    unsigned char unknown00[0x751], row, columns;
};
extern struct SceneModeFlags g_scene_mode_flags;
extern int condition_query_actor(void *, int);
extern void condition_update_actor(void *, int, int);
extern unsigned char condition_notification_active(unsigned int);

static inline unsigned int value_address(unsigned int row, unsigned int column,
                                         unsigned int entry)
{
    unsigned int base = (unsigned int)&g_resource_game_state;
    unsigned int offset = entry * 4;
    offset += column * 24;
    offset += row * 144;
    return offset + base;
}

static inline unsigned int *current_flags(void)
{
    unsigned int base = (unsigned int)&g_scene_mode_flags;
    unsigned int offset = g_transition_view_context.current_view * 56;
    base += 4;
    return (unsigned int *)(offset + base);
}

void resource_set_triple(unsigned int row, unsigned int column, unsigned int entry)
{
    unsigned int index, all;
    {
        union ResourceGameState *state = &g_resource_game_state;
        unsigned int offset = entry * 4;
        offset += column * 24;
        offset += row * 144;
        offset += (unsigned int)state;
        if (*(unsigned char *)(offset + 0x449) == 1)
            return;
        if (row == 4 && column == 4 && entry == 2) {
            void **actor = (void **)((unsigned char *)state + 0xf0);
            int answer = (signed char)condition_query_actor(*actor, 0x91);
            condition_update_actor(*actor, answer, 1);
        }
    }
    {
        unsigned char complete;
        unsigned int base = (unsigned int)&g_resource_game_state;
        unsigned int offset = entry * 4;
        offset += column * 24;
        offset += row * 144;
        offset += base;
        offset += 0x449;
        complete = 1;
        *(unsigned char *)offset = complete;
        all = complete;
    }
    for (index = 0; index < g_condition_definitions[row].columns[column]->count;
         index++) {
        if (!condition_group_active(row, column)) { all = 0; break; }
        if (!condition_is_complete(row, column, index)) { all = 0; break; }
    }
    if (column < g_condition_definitions[row].count &&
        entry < g_condition_definitions[row].columns[column]->count) {
        if (all && !condition_notification_active(condition_lookup_kind(row, column))) {
            struct ConditionSelection *selection =
                (struct ConditionSelection *)&g_resource_game_state;
            selection->row = row;
            selection->columns |= 1 << column;
            *current_flags() &= ~0x80000;
        } else if (*(unsigned char *)(value_address(row, column, entry) + 0x448)) {
            *current_flags() |= 0x80000;
        }
        {
            unsigned int address =
                (unsigned int)g_condition_definitions[row].columns[column];
            unsigned char kind;
            address += 4;
            address += entry;
            kind = *(unsigned char *)address;
            if (kind != 0xff) resource_set_display_kind(kind);
        }
        condition_refresh(row, column);
    }
}
