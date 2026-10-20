#include "display_menu_pages.h"

unsigned short display_read_map_tile(const unsigned short *tiles, int x, int y,
                                     int width)
{
    register const unsigned short *entry asm("r4") = tiles;
    {
        register unsigned int row_address asm("r0") = y;
        row_address *= width;
        row_address <<= 1;
        row_address = (unsigned int)entry + row_address;
        entry = (const unsigned short *)(row_address + 2 * x);
    }
    return *entry;
}
