#include "display.h"
void display_flush_pending_block(void)
{
    if (g_display_pending_block.pending) {
        display_copy_bytes(g_display_pending_block.staging, g_display_pending_block.queued, 0xb0);
        g_display_pending_block.pending = 0;
        g_display_pending_block_flag = 0;
    }
}
