#include "display_condition_panel.h"

void condition_panel_update_column_objects(unsigned int row)
{
    struct ConditionPanelDefinitionColumns *columns;
    struct ConditionPanelWorld *world;
    struct FrameObject **objects;
    unsigned int index, cell_offset, column_offset;
    index = 0;
    columns = g_condition_panel_definition_columns;
    cell_offset = 0;
    objects = g_condition_panel_objects;
    column_offset = 0;
    world = &g_condition_panel_world;
    for (; index <= 5; ++index) {
        unsigned int offset = column_offset + row * 32;
        unsigned int kind = (*(struct ConditionDefinition **)(offset + (unsigned int)columns))->unknown00;
        if (kind == 0) {
            (*objects)->flags &= ~1;
        } else {
            unsigned int row_offset = row * 144;
            unsigned int address = cell_offset + row_offset;
            address += (unsigned int)world;
            if (*(unsigned char *)(address + 0x444)) {
                (*objects)->unknown_0a = kind + 207;
                frame_set_variant_state(*objects, 58);
            } else {
                (*objects)->unknown_0a = 226;
                frame_set_variant_state(*objects, 58);
            }
            (*objects)->flags |= 1;
            display_scene_refresh_item(*objects);
        }
        cell_offset += 24;
        ++objects;
        column_offset += 4;
    }
}
asm(".align 2, 0");
