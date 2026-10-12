#include "irq.h"

void irq_wait_vblank(void) {
 volatile unsigned short *flags;
 unsigned int mask;
 g_irq_flags &= 0xFFFE;
 flags = &g_irq_flags;
 mask = 1;
again:
 if (!(*flags & mask)) goto again;
}
