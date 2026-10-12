#include "display.h"
void display_mark_tiles_free(unsigned short first, unsigned short count)
{
    unsigned int end, tile, byte, bit, mask;
    unsigned char *pending;
    if (first == 0xffff)
        return;
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
        pending = (unsigned char *)g_display_pending_free_tiles + byte;
        *pending &= ~mask;
    }
}
