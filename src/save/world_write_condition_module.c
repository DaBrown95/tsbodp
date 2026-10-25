#include "save_world_initialization.h"
#include "save_condition_state.h"

static inline unsigned int write_subfield_pair_and_next(const unsigned char *first_address,
                                                       unsigned int second_address)
{
    save_stream_write_bits(first_address, 1);
    save_stream_write_bits((const unsigned char *)second_address, 1);
    /* Keep the unused terminal block+725 address as an integer. */
    return second_address + 4;
}

void save_world_write_module_29d18(void)
{
    unsigned int group;
    unsigned int cell;
    unsigned int owner_address;
    unsigned int subcell;

    owner_address = (unsigned int)&g_save_world_condition_block;
    frame_write_save_value(&g_save_world_condition_block.selected, 1);
    group = 0;
    do {
        unsigned int next_group;
        register unsigned int working asm("r2");
        register unsigned int offset asm("r0");
        register unsigned char *group_base asm("r8");
        register unsigned int group_address asm("r1");

        cell = 0;
        offset = group * 8;
        working = group + 1;
        next_group = working;
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
            working = (unsigned int)group_base;
            entry = (unsigned char *)(working + cell_offset);
            save_stream_write_bits(entry, 1);
            save_stream_write_bits(entry + 1, 1);
            subcell = 0;
            next_cell = cell + 1;
            sub_offset = 4;
            cell_offset += 1;
            second_address = cell_offset + (unsigned int)group_base;
            second_address += 4;
            do {
                second_address = write_subfield_pair_and_next(entry + sub_offset, second_address);
                sub_offset += 4;
            } while (++subcell < 5);
            cell = next_cell;
        } while (cell < 6);
        group = next_group;
    } while (group < 5);
    save_stream_write_condition_display_bits();
}

asm(".align 2, 0");
