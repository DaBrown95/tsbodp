#include "resource_commands.h"
#include "resource_conditions.h"
#include "condition_actor.h"

struct ConditionPlayerSelection {
    unsigned char unknown00[0x440];
    unsigned int row;
};
extern struct SceneModeFlags g_scene_mode_flags;
extern void condition_update_actor_context(void *);

static inline unsigned int value_address(unsigned int row, unsigned int column,
                                         unsigned int entry)
{
    unsigned int base = (unsigned int)&g_resource_game_state;
    unsigned int offset = entry * 4;
    offset += column * 24;
    offset += row * 144;
    return offset + base;
}

static inline unsigned int group_address(unsigned int row, unsigned int column)
{
    unsigned int base = (unsigned int)&g_resource_game_state;
    unsigned int offset = column * 24;
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

void condition_activate_entry(unsigned int row, unsigned int column, unsigned int entry)
{
    {
        unsigned int address;
        union ResourceGameState *state = &g_resource_game_state;
        if (row == 1 && column == 0)
            ((struct ConditionPlayerSelection *)state)->row = 1;
        address = entry * 4;
        address += column * 24;
        address += row * 144;
        address += (unsigned int)state;
        if (!*(unsigned char *)(address + 0x448) &&
            column < g_condition_definitions[row].count &&
            entry < g_condition_definitions[row].columns[column]->count)
            *current_flags() |= 0x100000;
    }
    if (!*(unsigned char *)(group_address(row, column) + 0x444) &&
        column < g_condition_definitions[row].count) {
        struct ConditionDefinition *definition = g_condition_definitions[row].columns[column];
        if (entry < definition->count) {
            unsigned char kind = definition->group_display_kind;
            if (kind != 0xff)
                resource_set_display_kind(kind);
        }
    }
    *(unsigned char *)(group_address(row, column) + 0x444) = 1;
    *(unsigned char *)(value_address(row, column, entry) + 0x448) = 1;
    {
        unsigned char *state = (unsigned char *)&g_resource_game_state;
        unsigned char *actor = state + 0xdc;
        void *context;
        condition_record_actor_selection((struct ConditionActorSelectionContext *)actor,
                                         row, column, entry);
        context = state + 0x10;
        condition_update_actor_context(context);
        condition_finish_actor_context(context);
        if (actor[4] > 4)
            condition_complete_if_active(1, 4, 2);
        if (actor[4] > 29)
            condition_complete_if_active(4, 0, 2);
    }
    if (column < g_condition_definitions[row].count &&
        entry < g_condition_definitions[row].columns[column]->count)
        condition_refresh(row, column);
}
