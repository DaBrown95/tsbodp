#include "display.h"
#include "display_palette_lifecycle.h"
#include "heap.h"

void display_initialize_palette_pair(struct PaletteBufferPair *pair,
    unsigned short *destination)
{
    pair->staging = heap_allocate_zeroed(512);
    pair->destination = destination;
}
