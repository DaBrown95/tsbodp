#include "irq.h"

void irq_noop(void) {}

/* Explicit translation-unit alignment, matching the next ROM function. */
asm(".align 2, 0");
