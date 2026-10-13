#include "save_world_display.h"

void save_world_refresh_row_palette(unsigned int index)
{
    if (index == g_display_world_clock_selection.row) {
        display_load_resource_palette(&g_save_world_row_palette_a, 1);
        display_load_resource_palette(&g_save_world_row_palette_b, 2);
        display_load_palette_ranges(&g_save_world_row_palette_ranges);
    }
    {
        unsigned int base = (unsigned int)g_save_world_transition_rows;
        unsigned int offset = index * 56;
        base += 4;
        *(unsigned int *)(offset + base) &= ~0x400000u;
    }
}
