#include "display_map.h"

void display_write_incrementing_background_map(unsigned int index, int x, int y,
    int width, int height, unsigned short tile)
{
    int row;
    unsigned int record_offset;
    register int x_bytes __asm__("r8");
    row = 0;
    if (row < height) {
        record_offset = index * sizeof(struct DisplayMapState);
        x_bytes = x * 2;
        do {
            if (width > 0) {
                unsigned int address = y + row;
                struct DisplayMapState *background = (struct DisplayMapState *)
                    ((char *)g_display_map_states + record_offset);
                unsigned short *map;
                unsigned int flags;
                register unsigned int dirty __asm__("r6");
                address *= 64;
                map = background->map;
                flags = background->flags;
                /* Wrapped addition via the inverse row offset preserves the
                 * pinned compiler's allocation without instruction assembly. */
                address = (unsigned int)map + x_bytes - -address;
                dirty = 0x20;
                {
                    int count = width;
                    do {
                        *(unsigned short *)address = tile;
                        flags |= dirty;
                        ++tile;
                        address += 2;
                    } while (--count);
                }
                background->flags = flags;
            }
        } while (++row < height);
    }
}
