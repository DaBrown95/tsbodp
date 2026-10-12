#include "display.h"
void display_load_palette(const void *source, unsigned int first, unsigned int count)
{
    display_transfer_palette(source, first, count, &g_palette_buffer_pairs[0]);
}
