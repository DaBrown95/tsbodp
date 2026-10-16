#include "display_condition_panel_setup.h"

/* The row table has the existing 32-byte stride. Both values die at the
 * returned pointer; neither remains in a scratch register across a call. */
static inline struct ConditionRow *panel_definition_for_row(unsigned int row)
{
    unsigned int root;
    unsigned int offset;
    root = (unsigned int)g_condition_definitions;
    offset = row * 32;
    return (struct ConditionRow *)(offset + root);
}

void condition_panel_initialize(void)
{
    unsigned int control;
    display_set_mode(0);
    display_enable_layers(0x1000);
    display_show_background(3, g_condition_panel_control3);
    display_show_background(2, g_condition_panel_control2);
    display_show_background(1, g_condition_panel_control1);
    display_fill_background(1, 0);
    control = g_condition_panel_control0;
    display_show_background(0, control);
    display_fill_background(0, 0);
    display_text_set_background_control(control);
    {
        struct DisplaySceneRequestState *request;
        struct ConditionPanelWorld *initial_world;
        unsigned int row;
        unsigned int initial_row_offset;
        unsigned int initial_address;
        unsigned int second_offset;
        request = &g_display_scene_request_state;
        request->scene = 0;
        initial_world = &g_condition_panel_world;
        row = initial_world->row;
        request->parameter = row;
        request->mode = 1;
        {
            unsigned int row_units;
            row_units = row * 9;
            initial_row_offset = row_units << 4;
        }
        initial_address = initial_row_offset + (unsigned int)initial_world;
        second_offset = 0x445;
        if (*(unsigned char *)(initial_address + second_offset)) {
            unsigned int row_offset;
            struct ConditionPanelWorld *loop_world;
            struct ConditionRow *definition;
            unsigned int active_offset;
            unsigned int cell_address;
            loop_world = initial_world;
            row_offset = initial_row_offset;
            definition = panel_definition_for_row(row);
            active_offset = 0x444;
            do {
                unsigned int next = request->scene + 1;
                unsigned int cell_offset = next * 24;
                cell_offset += row_offset;
                cell_address = cell_offset + (unsigned int)loop_world;
                if (!*(unsigned char *)(cell_address + active_offset))
                    break;
                request->scene = next;
                if ((int)definition->count - 1 == next)
                    break;
            } while (*(unsigned char *)(cell_address + second_offset));
        }
    }
    display_load_background(3, &g_condition_panel_background3, 0, 4, 0, 0);
    display_set_background_velocity(3, 32768, 32768);
    display_load_background(2, &g_condition_panel_background2, 4, 1, 0, 0);
    scene_view_load_selected_resource(1, 3, 1, 1, 6,
        (const SceneViewResourceSelectionByte *)((unsigned char *)&g_condition_panel_world + 0x20));
    display_load_resource_palette(&g_condition_panel_palette0, 0);
    display_load_resource_palette(&g_condition_panel_palette7, 7);
    display_load_palette_ranges(&g_condition_panel_ranges);
    {
        unsigned int tile;
        unsigned int heading_style;
        register unsigned int number_style asm("r5");
        const char *heading;
        /* The second line style is a real callee-saved value across the
         * intervening font, number-field and lookup calls. */
        heading_style = 1;
        display_text_select_font(3, 0, 0);
        heading = display_scene_lookup_text(444);
        number_style = 1;
        tile = display_text_draw_line(1, 114, 4, heading, heading_style);
        display_text_select_font(3, 0, 0);
        display_text_number_field_zero(g_condition_panel_world.number);
        display_text_draw_line(tile, 88, 26, display_scene_lookup_text(6220), number_style);
    }
    condition_panel_create_objects();
    condition_panel_draw_row_labels(g_display_scene_request_state.parameter);
    condition_panel_update_column_objects(g_display_scene_request_state.parameter);
    condition_panel_draw_details(g_display_scene_request_state.parameter, g_display_scene_request_state.scene);
    transition_run_first(63, 0);
}
asm(".align 2, 0");
