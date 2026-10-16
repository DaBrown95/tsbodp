#include "display_pending_scroll.h"

void display_reset_pending_to_default(void)
{
    display_queue_pending_rows(g_display_default_pending_rows, 1);
    irq_wait_vblank();
}
