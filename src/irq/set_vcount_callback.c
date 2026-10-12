#include "irq.h"

void set_vcount_callback(IrqCallback callback) {
 if (!callback) g_irq_context->vcount = irq_noop;
 else g_irq_context->vcount = callback;
}
