#include "heap.h"

void heap_initialize(void)
{
    unsigned int offset = g_heap_span_end - g_heap_span_begin;
    unsigned int remainder = offset & 15;
    if (remainder) offset += 16 - remainder;
    heap_initialize_arena(0, (void *)(0x02000000 + offset), (void *)0x02040000);
}
