#include "display.h"
void display_flush_palette_queue(void)
{
    register unsigned int i __asm__("r5");
    register struct PaletteQueueEntry *entry __asm__("r4");
    register volatile unsigned int *base __asm__("r6");
    unsigned int address;
    register unsigned int source_base __asm__("r1");
    i = 0;
    if (i < g_palette_queue_count) {
        entry = (struct PaletteQueueEntry *)g_palette_queue_words;
        base = (volatile unsigned int *)entry;
        do {
            address = i * 8;
            source_base = (unsigned int)base + 4;
            address += source_base;
            display_transfer_palette(*(const void **)address, entry->first,
                                     entry->count, &g_palette_buffer_pairs[1]);
            ++entry;
            ++i;
        } while (i < g_palette_queue_count);
    }
    g_palette_queue_count = 0;
}
