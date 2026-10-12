#include "irq.h"

void irq_vcount(void) {
 if (g_irq_context->vcount) g_irq_context->vcount();
 g_irq_context->vcount_count++;
 REG16(0x04000202) = 4;
 g_irq_flags |= 4;
}
