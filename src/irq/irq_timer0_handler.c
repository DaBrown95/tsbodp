#include "irq.h"

void irq_timer0_handler(void) {
 g_irq_context->timer0_count++;
 REG16(0x04000202) = 8;
 g_irq_flags |= 8;
}
