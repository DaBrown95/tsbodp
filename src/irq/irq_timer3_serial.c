#include "irq.h"

void irq_timer3_serial(void) {
 g_irq_context->timer3_serial_count++;
 REG16(0x04000202) = 64;
 g_irq_flags |= 64;
}
