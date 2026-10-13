#include "display_condition_panel.h"

void condition_panel_create_objects(void)
{
    struct ConditionPanelWorld *world;
    int index;

    {
        struct FrameObject **objects;
        register struct FrameObject *created asm("r0");
        created = frame_create_scene_object(
            g_display_scene_request_state.scene + 82, 10, 1, 1);
        objects = g_condition_panel_objects;
        objects[8] = created;
        objects[6] = frame_create_scene_object(93, 236, 7, 1);
        objects[7] = frame_create_scene_object(94, 237, 7, 1);
        {
            struct ConditionPanelWorld *row_source;
            row_source = &g_condition_panel_world;
            objects[9] = frame_create_scene_object(row_source->row + 77, 227, 14, 1);
        }
    }

    {
        register struct FrameObject *created asm("r0");
        struct FrameObject **objects;
        for (index = 5, world = &g_condition_panel_world; index >= 0; --index) {
            unsigned int row = world->row;
            unsigned int subtype;
            unsigned int offset = index * 24 + row * 144;
            unsigned int address = offset + (unsigned int)world;
            if (*(unsigned char *)(address + 0x444))
                subtype = g_condition_panel_definition_columns[row].entries[index]->unknown00 + 207;
            else
                subtype = 226;
            created = frame_create_scene_object(index + 82, subtype, index + 8, 0);
            *(struct FrameObject **)(index * 4 + (unsigned int)g_condition_panel_objects) = created;
        }
        index = 10;
        objects = g_condition_panel_objects + index;
        for (; index <= 14; ++index)
            *objects++ = frame_create_scene_object(index + 78, 228, 15, 0);
    }
}
asm(".align 2, 0");
