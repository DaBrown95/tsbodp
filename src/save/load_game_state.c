#include "save_game_loading.h"
#include "save_world_initialization.h"
#include "resource_conditions.h"
#include "frame_actor_scene.h"
#include "save_condition_state.h"

static inline unsigned int save_condition_count_offset(struct ConditionPanelDefinitionColumns *table, unsigned int row, unsigned int column_offset)
{
    unsigned int offset = column_offset;
    struct ConditionDefinition *definition;
    offset += row * sizeof(struct ConditionRow);
    offset += (unsigned int) table;
    definition = *((struct ConditionDefinition **) offset);
    return definition->count;
}

static inline struct ConditionDefinition *save_load_condition_definition(struct ConditionPanelDefinitionColumns *table, unsigned int row, unsigned int column_offset)
{
    unsigned int offset = column_offset;
    offset += row * sizeof(struct ConditionRow);
    offset += (unsigned int) table;
    return *((struct ConditionDefinition **) offset);
}

void save_stream_load_game_state(void)
{
    struct SaveWorldInitState *world = &g_save_world_init_state;
    /* Shared selected-word address uses the fixed 32-bit RAM view. */
    unsigned int world_address;
    unsigned char *selection;
    signed char *first;
    signed char *second;
    register unsigned int column asm("r5");
    register unsigned int entry asm("r4");
    unsigned int all;
    unsigned int *row;
    ((unsigned char *) world)[0x73f] = 14;
    frame_load_save_value(&g_save_serialized_marker, 1);
    frame_load_save_value(&world->prefix.unknown00, 4);
    frame_load_save_value(&world->prefix.clock, 6);
    frame_load_save_value(&world->prefix.unknown04, 3);
    if (world->prefix.unknown04 & 0x800000)
    {
        world->prefix.unknown04 |= 0xff000000;
    }
    save_stream_read_world_record((struct SaveStreamWorldRecord *) world->prefix.unknown10);
    save_stream_read_actor_entries(world->prefix.unknowndc);
    /* The load reset shares the first scene-mode byte. */
    g_scene_mode_bytes[0] = 255;
    selection = g_save_selection_prefix;
    frame_load_save_value(selection, 1);
    frame_load_save_value(selection + 1, 2);
    frame_load_save_value(selection + 3, 2);
    save_stream_read_bits(&world->prefix.bit747, 1);
    save_stream_read_bits((unsigned char *) (&g_save_world_rows[selection[42]].unknown00), 1);
    save_stream_read_bits(&world->prefix.bit749, 1);
    frame_load_save_value(&world->prefix.byte741, 1);
    frame_load_save_value(&world->prefix.byte742, 1);
    frame_load_save_value(&world->prefix.byte746, 1);
    frame_load_save_value(&world->prefix.short744, 2);
    first = (signed char *) (&world->prefix.byte726);
    frame_load_save_value(first, 1);
    second = (signed char *) (&world->prefix.byte72e);
    frame_load_save_value(second, 1);
    frame_load_save_value(&g_save_world_event, 1);
    save_read_condition_state();
    save_stream_read_nibble_state();
    save_stream_read_world_fields();
    save_stream_read_auxiliary_fields();
    save_stream_read_flag_words();
    frame_load_save_value(&world->prefix.byte740, 1);
    if (((*first) == 0) && ((*second) == 0))
    {
        ((unsigned char *) world)[0x734] = 0;
    }
    {
        register unsigned int address asm("r2");
        register int *pending asm("r1");
        address = (unsigned int) (&g_save_world_init_state);
        pending = (int *) (address + 0x74c);
        *pending = -2;
    }
    {
        register struct ConditionPanelDefinitionColumns *columns asm("r10");
        column = 0;
        world_address = (unsigned int) (&g_save_world_init_state);
        columns = g_condition_panel_definition_columns;
        do
        {
            unsigned int offset;
            unsigned int next_column;
            unsigned int temporary_offset;
            struct ConditionDefinition *definition;
            all = 1;
            entry = 0;
            temporary_offset = column * 4;
            {
                register unsigned int selected_row_root asm("r3");
                register unsigned int selected_row_offset asm("r1");
                selected_row_root = world_address;
                selected_row_offset = 0x440;
                selected_row_root += selected_row_offset;
                row = (unsigned int *) selected_row_root;
            }
            definition = save_load_condition_definition(columns, *row, temporary_offset);
            offset = temporary_offset;
            next_column = column + 1;
            if (entry < definition->count)
            {
                unsigned int *current = row;
                do
                {
                    if (!((unsigned char) condition_is_complete(*current, column, entry)))
                    {
                        all = 0;
                        break;
                    }
                    ++entry;
                }
                while (entry < save_condition_count_offset(g_condition_panel_definition_columns, *current, offset));
            }
            if (all)
            {
                struct SaveWorldInitState *completion = &g_save_world_init_state;
                unsigned int *current = (unsigned int *) (((unsigned int) completion) + 0x440);
                if ((!(((*current) == 0) && (column == 5))) && (!((unsigned char) condition_group_complete(*current, column))))
                {
                    completion->pending_columns |= 1 << column;
                    completion->pending_row = *current;
                }
            }
            column = next_column;
        }
        while (column <= 5);
    }
}

asm(".align 2, 0");
