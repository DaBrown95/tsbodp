#include "display.h"
void display_write_background_map(unsigned int index, const unsigned short *map,
    unsigned short tile_offset, unsigned short palette_bank,
    unsigned int destination_x, unsigned int destination_y)
{
    struct BackgroundState *background = &g_background_states[index];
    const unsigned char *source = (const unsigned char *)map + 4;
    register unsigned short *destination __asm__("r3") = background->tilemap_buffer;
    unsigned int width, height, column, flags;
    unsigned int next_row;
    register unsigned int stride __asm__("r9");
    register unsigned int row __asm__("r1");
    unsigned int size;
    if (!(((struct DisplayControlState *)((unsigned int)g_background_states - 8U))->control & 7) || index <= 1) {
        destination += destination_y * 32 + destination_x;
        width = map[0] < 32 ? map[0] : 32;
        height = map[1] < 32 ? map[1] : 32;
        row = height;
        flags = background->flags;
        if (row) {
        stride = (32 - width) * 2;
        do {
            column = width;
            next_row = row - 1;
            while (column) {
                *destination++ = *(const unsigned short *)source + (palette_bank << 12) + tile_offset;
                source += 2;
                --column;
            }
            destination = (unsigned short *)((unsigned char *)destination + stride);
            source += (map[0] - width) * 2;
            row = next_row;
        } while(row);
        }
        if (map[0] > 32 && ((size = ((unsigned char *)&background->registers.control)[1] & 0xc0) == 0x40 || size == 0xc0)) {
            destination += (32 - height) * 32;
            source = (const unsigned char *)map + 4;
            width = map[0] - 32;
            row = height;
            if (row) {
            stride = (32 - width) * 2;
            do {
                source += 64;
                column = width;
                next_row = row - 1;
                while (column) {
                    *destination++ = *(const unsigned short *)source + (palette_bank << 12) + tile_offset;
                    source += 2;
                    --column;
                }
                destination = (unsigned short *)((unsigned char *)destination + stride);
                row = next_row;
            } while(row);
            }
        }
        if (map[1] > 32 && ((size = ((unsigned char *)&background->registers.control)[1] & 0xc0) == 0x80 || size == 0xc0)) {
            width = map[0] < 32 ? map[0] : 32;
            height=map[1]; row=height-32; height=row;
            if (row) {
            stride = (32 - width) * 2;
            do {
                column = width;
                next_row = row - 1;
                while (column) {
                    *destination++ = *(const unsigned short *)source + (palette_bank << 12) + tile_offset;
                    source += 2;
                    --column;
                }
                destination = (unsigned short *)((unsigned char *)destination + stride);
                source += (map[0] - width) * 2;
                row = next_row;
            } while(row);
            }
        }
        if (map[0] > 32 && map[1] > 32 && (((unsigned char *)&background->registers.control)[1] & 0xc0) == 0xc0) {
            destination += (32 - height) * 32;
            size = map[0];
            source = (const unsigned char *)map + (size * 64 + 4);
            width = size - 32;
            row = height;
            if (row) {
            unsigned int last_stride = (32 - width) * 2;
            do {
                source += 64;
                column = width;
                next_row = row - 1;
                while (column) {
                    *destination++ = *(const unsigned short *)source + (palette_bank << 12) + tile_offset;
                    source += 2;
                    --column;
                }
                destination = (unsigned short *)((unsigned char *)destination + last_stride);
                row = next_row;
            } while(row);
            }
        }
    } else {
        register unsigned char *bytes __asm__("r5");
        register unsigned int aligned_address __asm__("r3");
        unsigned int value, incoming;
        unsigned int size_code = ((unsigned char *)&background->registers.control)[1] >> 6;
        stride = 16;
        stride <<= size_code;
        {
            register unsigned int row_address __asm__("r0") = (unsigned int)destination + stride * destination_y;
            bytes = (unsigned char *)(row_address + destination_x);
        }
        row = map[1];
        flags = background->flags;
        while (row) {
            aligned_address = ~1U;
            aligned_address &= (unsigned int)bytes;
            column = map[0];
            next_row = row - 1;
            while (column) {
                if ((unsigned int)bytes & 1) {
                    value = *(unsigned char *)aligned_address;
                    incoming = (*source << 8) + tile_offset;
                    goto partial_store;
                }
                if (column != 1)
                    goto pair_store;
                value = *(unsigned short *)aligned_address & 0xff00;
                incoming = *source + tile_offset;
            partial_store:
                *(unsigned short *)aligned_address = value | incoming;
                goto advance_cursors;
            pair_store:
                value = source[0] + tile_offset;
                incoming = (source[1] + tile_offset) << 8;
                *(unsigned short *)aligned_address = value | incoming;
                ++bytes;
                ++source;
            advance_cursors:
                aligned_address += 2;
                ++bytes;
                ++source;
                --column;
            }
            bytes += stride - map[0];
            row = next_row;
        }
    }
    background->flags = flags | 0x20;
}
