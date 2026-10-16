#include "display_pending_block.h"
#include "display.h"

void display_initialize_pending_block(void)
{
    g_display_pending_block_flag = 0;
    display_reset_queued_rows();
    display_queue_pending_rows(g_display_default_pending_rows, 1);
    heap_copy(g_display_pending_block.staging, g_display_pending_block.queued, 176);
    set_vcount_callback(display_pending_vcount_callback);
    display_arm_pending_vcount();
}
