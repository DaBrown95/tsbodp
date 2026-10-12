#include "irq.h"

void irq_init(void) {
 volatile unsigned int *dma;
 g_irq_context = &g_irq_context_storage;
 dma = (volatile unsigned int *)0x040000D4;
 dma[0] = (unsigned int)g_irq_dispatcher_rom;
 dma[1] = (unsigned int)g_irq_dispatcher_ram;
 dma[2] = 0x84000080;
 (void)dma[2];
 REG32(0x03007FFC) = (unsigned int)g_irq_dispatcher_ram;
 dma[0] = (unsigned int)g_irq_defaults;
 dma[1] = (unsigned int)g_irq_table;
 dma[2] = 0x8400000D;
 (void)dma[2];
}
