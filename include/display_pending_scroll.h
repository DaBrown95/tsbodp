#ifndef DISPLAY_PENDING_SCROLL_H
#define DISPLAY_PENDING_SCROLL_H
#include "display_pending_block.h"

/* These adjacent row-ABI callbacks update fixed-point state and wait for HBlank.
 * No assignment establishes them as members of the pending-row target domain. */
void display_pending_step_bg3_x(unsigned int *, unsigned int *);
void display_pending_step_bg2_x(unsigned int *, unsigned int *);
void display_disable_pending_vcount(void);
void display_reset_pending_to_default(void);
void irq_wait_vblank(void);
#endif
