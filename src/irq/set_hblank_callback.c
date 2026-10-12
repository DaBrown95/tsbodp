#include "irq.h"

void set_hblank_callback(IrqCallback callback) {
 if (!callback) g_irq_context->hblank = irq_noop;
 else g_irq_context->hblank = callback;
}
