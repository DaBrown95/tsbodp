#include "display.h"
void display_queue_palette(const void *source, unsigned int first, unsigned int count)
{
    register unsigned int *count_pointer asm("r8") = &g_palette_queue_count;
    unsigned int index = *count_pointer;
    unsigned char *base = (unsigned char *)g_palette_queue;
    unsigned int offset = index * 8;
    struct PaletteQueueEntry *entry;
    { const void **pointer=(const void **)(base + 4); pointer=(const void **)((unsigned int)pointer+offset); *pointer = source; }
    entry = (struct PaletteQueueEntry *)(base + offset);
    entry->first = first;
    entry->count = count;
    ++index;
    *count_pointer = index;
}
