#include "display_condition_panel_details.h"

static inline unsigned int panel_count(unsigned int row, unsigned int column)
{
    unsigned int root;
    const struct ConditionDefinition *definition;
    unsigned int row_stride;
    unsigned int offset;

    root = (unsigned int)g_condition_definitions;
    row_stride = row * 32;
    offset = column * 4 + row_stride;
    root += 8;
    definition = *(const struct ConditionDefinition **)(offset + root);
    return definition->count;
}

void condition_panel_draw_details(unsigned int row, unsigned int column)
{
    register unsigned int tile asm("r9");
    const unsigned int (*titles)[6];
    unsigned int title;

    display_fill_background_constant_rectangle(0, 0, 10, 30, 10, 0);
    tile = 91;
    {
        register const unsigned int *title_source asm("r10");
        title_source = (const unsigned int *)g_condition_panel_text_ids;
        title = *(const unsigned int *)(row * 24 + column * 4 +
                                        (unsigned int)title_source);
    }
    titles = g_condition_panel_text_ids;
    if (title) {
        unsigned char index;
        unsigned int column_pairs, row_blocks;
        {
            register struct ConditionPanelWorld *cell_source asm("r8");
            unsigned int offset;
            unsigned int active;
            register unsigned int column_offset asm("r1");
            register unsigned int initial_column_pairs asm("r3");
            register unsigned int initial_row_blocks asm("r2");

            cell_source = &g_condition_panel_world;
            initial_column_pairs = column * 2;
            column_offset = (initial_column_pairs + column) * 8;
            initial_row_blocks = row * 8;
            offset = column_offset + (initial_row_blocks + row) * 16;
            active = *(unsigned char *)(offset + (unsigned int)cell_source + 0x444);
            /* These factors outlive the initial predicate, not its scratch
             * registers. Their copies are retained across the draw calls. */
            column_pairs = initial_column_pairs;
            row_blocks = initial_row_blocks;
            if (active) {
                display_text_select_font(3, 3, 0);
                tile = display_text_draw_line(
                    91, 120, 84, display_scene_lookup_text(title), 1);
            }
        }
        display_text_select_font(3, 0, -1);
        for (index = 0; index < panel_count(row, column); ++index) {
            unsigned int offset = index * 4 + (column_pairs + column) * 8;
            unsigned int address;
            offset += (row_blocks + row) * 16;
            address = offset + (unsigned int)&g_condition_panel_world;
            if (*(unsigned char *)(address + 0x448)) {
                tile = display_text_draw_line(
                    tile, 26, index * 12 + 96,
                    display_scene_lookup_text(
                        *(const unsigned int *)(row * 24 + column * 4 +
                                                (unsigned int)titles) + index + 1),
                    0);
                g_condition_panel_objects[index + 10]->flags |= 1;
                if (*(unsigned char *)(address + 0x449))
                    frame_set_animation_frame(
                        (struct FrameTickObject *)g_condition_panel_objects[index + 10], 1);
                else
                    frame_set_animation_frame(
                        (struct FrameTickObject *)g_condition_panel_objects[index + 10], 0);
            } else {
                g_condition_panel_objects[index + 10]->flags &= ~1;
            }
        }
        while (index <= 4) {
            g_condition_panel_objects[index + 10]->flags &= ~1;
            ++index;
        }
    }
}
asm(".align 2, 0");
