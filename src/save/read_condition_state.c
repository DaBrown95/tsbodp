#include "save_world_initialization.h"
#include "save_condition_state.h"

static inline void read_counted_flag(unsigned char *destination,
                                     unsigned char count)
{
    save_stream_read_bits(destination, count);
}

void save_read_condition_state(void)
{
    unsigned int group, cell, subcell;
    unsigned int owner_address;

    owner_address = (unsigned int)&g_save_world_condition_block;

    frame_load_save_value(&g_save_world_condition_block.selected, 1);
    group = 0;
    do {
        unsigned int next_group;
        register unsigned int offset asm("r0");
        register unsigned char *group_base asm("r8");
        register unsigned int group_address asm("r1");

        cell = 0;
        offset = group * 8;
        next_group = group + 1;
        offset += group;
        offset *= 16;
        offset += 4;
        group_address = owner_address;
        group_address += offset;
        group_base = (unsigned char *)group_address;
        do {
            unsigned int cell_offset;
            unsigned char *entry;
            unsigned int next_cell;
            unsigned int sub_offset;
            unsigned int second_address;

            cell_offset = cell * 24;
            entry = (unsigned char *)((unsigned int)group_base + cell_offset);
            read_counted_flag(entry, 1);
            read_counted_flag(entry + 1, 1);
            subcell = 0;
            next_cell = cell + 1;
            sub_offset = 4;
            cell_offset += 1;
            second_address = cell_offset + (unsigned int)group_base;
            second_address += 4;
            do {
                read_counted_flag(entry + sub_offset, 1);
                read_counted_flag((unsigned char *)second_address, 1);
                /* The unused final address is block+725, outside the
                 * 724-byte partial owner. Advance the actual integer address. */
                second_address += 4;
                sub_offset += 4;
            } while (++subcell < 5);
            cell = next_cell;
        } while (cell < 6);
        group = next_group;
    } while (group < 5);
    save_stream_read_condition_display_bits();
}

asm(".align 2, 0");
