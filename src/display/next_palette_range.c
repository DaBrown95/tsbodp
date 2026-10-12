#include "display.h"
unsigned int display_next_palette_range(void)
{
    register unsigned int count __asm__("r2") = g_palette_range_count;
    unsigned int index = count;
    ++count;
    g_palette_range_count = count;
    return index;
}
