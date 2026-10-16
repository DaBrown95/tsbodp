#include "startup_memory.h"

void startup_clear_vram(void)
{
    unsigned short zero;
    unsigned short *fill = &zero;
    *fill = 0;
    STARTUP_DMA3->source = (unsigned int)&zero;
    STARTUP_DMA3->destination = 0x06000000;
    STARTUP_DMA3->control = 0x8100c000;
    (void)STARTUP_DMA3->control;
}
