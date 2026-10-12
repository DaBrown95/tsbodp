#include "irq.h"

/* Unmatched WIP. Not part of the accepted source coverage or ROM link. */

void irq_wait_vblank(void) {
 volatile unsigned short *flags;
 g_irq_flags &= 0xFFFE;
 flags = &g_irq_flags;
again:
 if (!(*flags & 1)) goto again;
}
