#include "irq.h"

void irq_hblank(void) {
 if (g_irq_context->hblank) g_irq_context->hblank();
 g_irq_context->hblank_count++;
 REG16(0x04000202) = 2;
 g_irq_flags |= 2;
}
