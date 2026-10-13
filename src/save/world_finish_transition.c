#include "save_world_display.h"
#include "display.h"
#include "display_window_motion.h"

/* The flag address retains the observed base-plus-four and byte-offset views. */
static inline unsigned int *save_world_row_flags_address(
    unsigned int base, unsigned int offset)
{
    register unsigned int address asm("r1");
    address = base;
    address += 4;
    return (unsigned int *)(offset + address);
}

void save_world_finish_transition(unsigned int index, unsigned char immediate)
{
    if (immediate == 1)
        g_save_world_transition_rows[index].ticks = 0;
    else
        g_save_world_transition_rows[index].ticks = 20;
    {
        unsigned int base = (unsigned int)g_save_world_transition_rows;
        register unsigned int seven_index asm("r0");
        register unsigned int offset asm("r6");
        struct SaveWorldTransitionRow *row;

        seven_index = (index << 3) - index;
        offset = seven_index << 3;
        row = (struct SaveWorldTransitionRow *)(base + offset);
        if (row->ticks) {
            display_configure_window(1, 62, 63);
            display_set_window_rectangle(1, 40 << 16, 120 << 16,
                                         240 << 16, 160 << 16);
            display_begin_window_axis_move(1, 1, 240 << 16, 120 << 16, 20);
        }
        display_write_background_map(0, g_save_world_transition_map, 1, 1, 5, 15);
        *save_world_row_flags_address(base, offset) |= 0x3fc;
        save_world_update_row_gauges();
        row->ready = 1;
    }
}
