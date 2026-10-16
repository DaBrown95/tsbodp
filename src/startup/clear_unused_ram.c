#include "startup_memory.h"

void startup_clear_unused_ram(void)
{
    unsigned int iwram_bytes = g_startup_iwram_span_end - g_startup_iwram_span_begin;
    unsigned int ewram_bytes = g_heap_span_end - g_heap_span_begin;
    unsigned int zero;

    zero = 0;
    STARTUP_DMA3->source = (unsigned int)&zero;
    STARTUP_DMA3->destination = 0x03000000 + iwram_bytes;
    STARTUP_DMA3->control = ((0x7d00 - iwram_bytes) >> 2) | 0x85000000;
    (void)STARTUP_DMA3->control;

    zero = 0;
    STARTUP_DMA3->source = (unsigned int)&zero;
    STARTUP_DMA3->destination = 0x02000000 + ewram_bytes;
    STARTUP_DMA3->control = ((0x40000 - ewram_bytes) >> 2) | 0x85000000;
    (void)STARTUP_DMA3->control;
}
