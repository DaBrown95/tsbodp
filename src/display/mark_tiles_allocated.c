#include "display.h"
void display_mark_tiles_allocated(unsigned short first, unsigned short count)
{
    unsigned int end, tile, byte, bit, mask;
    unsigned char *pending;
    end = first + count;
    for (tile = first; tile < end;) {
        byte = tile >> 3;
        bit = tile & 7;
        if (!bit && end - tile > 7) {
            mask = 0xff;
            tile += 8;
        } else {
            mask = 1 << bit;
            ++tile;
        }
        pending = (unsigned char *)g_display_allocated_tiles + byte;
        *pending |= mask;
    }
}
