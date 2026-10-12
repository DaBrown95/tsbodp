#include "display.h"
void display_release_tile_bytes(unsigned short first, unsigned int bytes, unsigned char small_tiles)
{
    unsigned int count = bytes >> 6;
    if (small_tiles)
        count = bytes >> 5;
    display_mark_tiles_free(first, (unsigned short)count);
}
/* The original extent has zero alignment after the pool-free Thumb body. */
__asm__(".align 2, 0");
