#include "irq.h"

void irq_default_vblank_callback(void) { frame_update(); }

/* Explicit translation-unit alignment, matching the next ROM function. */
asm(".align 2, 0");
