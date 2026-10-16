#include "startup_memory.h"

void startup_clear_oam(void)
{
    unsigned int zero = 0;
    STARTUP_DMA3->source = (unsigned int)&zero;
    STARTUP_DMA3->destination = 0x07000000;
    STARTUP_DMA3->control = 0x85000100;
    (void)STARTUP_DMA3->control;
}
