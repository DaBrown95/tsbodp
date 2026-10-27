#include "display_text_raster.h"

static __inline unsigned int text_flip_bytes(void)
{
    register const struct DisplayTextRasterState *state asm("r6") = &g_display_text_state;
    return state->tile_bytes;
}

void display_text_read_rows(unsigned int *destination, unsigned int rows,
                            const unsigned short *input_map, const void *input_tiles)
{
    register const unsigned short *map asm("r6") = input_map;
    register const void *tiles asm("r10") = input_tiles;

    --rows;
    if (rows != -1U) {
        register unsigned int finished asm("r9") = -1U;
        do {
            register unsigned int entry asm("r3") = *map;
            register unsigned short tile_mask asm("r1") = 0x3ff;
            register unsigned int row_work asm("r1") = tile_mask;
            register unsigned int tile_bytes asm("r2");
            unsigned int source_offset;
            const unsigned int *source;
            unsigned int words;
            unsigned int next_rows;
            const unsigned short *next_map;

            row_work &= entry;
            tile_bytes = g_display_text_state.tile_bytes;
            source_offset = row_work * tile_bytes;
            source = (const void *)((const unsigned char *)tiles + source_offset);
            words = tile_bytes >> 2;
            --words;
            next_rows = rows - 1U;
            next_map = map + 32;
            if (words != finished) {
                row_work = -1U;
                do {
                    *destination++ = *source++;
                    --words;
                } while (words != row_work);
            }
            row_work = 0x400;
            {
                /* The map entry bounds this result to sixteen bits. */
                register unsigned short test asm("r0") = row_work & entry;
                if (test)
                    display_text_flip_tile((unsigned char *)destination - text_flip_bytes());
            }
            map = next_map;
            rows = next_rows;
        } while (rows != finished);
    }
}

__asm__(".align 2,0");
