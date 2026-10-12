#include "irq.h"

void set_vblank_callback(IrqCallback callback) {
 if (!callback) g_irq_context->vblank = irq_noop;
 else g_irq_context->vblank = callback;
}
