#include "save_world_initialization.h"

void save_world_clear_row_objects(void)
{
    unsigned int index = 0;
    struct SaveWorldTransitionRow *table = g_save_world_transition_rows;
    const unsigned char *selection = &g_display_world_clock_selection.row;
    do {
        unsigned int slot_offset = index * 4;
        unsigned int row_offset = *selection * 56;
        register unsigned int objects_address asm("r0");
        slot_offset += row_offset;
        objects_address = (unsigned int)table;
        objects_address += 16;
        if (*(struct FrameObject **)(slot_offset + objects_address))
            save_world_release_row_object((struct SaveWorldTransitionRow *)
                (row_offset + (unsigned int)table), index);
        ++index;
    } while (index <= 7);
}
asm(".align 2, 0");
